#include "../../includes/Server.hpp"
#include "../../includes/Client.hpp"
#include "../../includes/Channel.hpp"
#include "../../includes/Parser.hpp"
#include <iostream>


volatile sig_atomic_t g_running = 1;

// Handler appelé quand on reçoit SIGINT (Ctrl+C) ou SIGQUIT (Ctrl+\)
void signalHandler(int signum)
{
	(void)signum;
	std::cout << "\nShutting down server..." << std::endl;
	g_running = 0;
}

Server::Server(int port, const std::string& password): _serverFd(-1), _port(port), _password(password)
{
	_initSocket();
}

Server::~Server()
{
    // Nettoyer tous les clients (libérer la mémoire)
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
        delete it->second;
    _clients.clear();

    // Nettoyer tous les channels (libérer la mémoire)
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
        delete it->second;
    _channels.clear();

    // Fermer tous les sockets clients
	for (std::vector<struct pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); it++)
	{
		if (it->fd != _serverFd)
			close(it->fd);		
	}
	if (_serverFd != -1)
		close(_serverFd);		
}
// Forme canonique
Server::Server(const Server& other) : _serverFd(-1), _port(0)
{
    (void)other;
}

Server& Server::operator=(const Server& other)
{
    (void)other;
    return *this;
}

// Getters
const std::string& Server::getPassword() const { return _password; }
int Server::getPort() const { return _port; }

void Server::_initSocket()
{
	// SOCK_STREAM = tcp sdonc fiable et securise
	// AF_INET = ipv4
	// 0 = protocol de base
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
		std::cout << "EROOR initializing socket" << std::endl;
	int opt = 1;
	// opt = 1 active cette option 0 desactive
// 	SO_REUSEADDR
//   - Permet de réutiliser immédiatement le port après fermeture du serveur
//   - Sans ça : "Address already in use" pendant ~2 minutes après un crash
	 if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0 )
		std::cout << "EROOR opt failed" << std::endl;
	fcntl(serverSocket, F_SETFL, O_NONBLOCK);
	// sans ca accept et recv bloque le serv en attendant les donnes
	struct sockaddr_in servAddress;
		servAddress.sin_family = AF_INET;
		// IPv4
		servAddress.sin_port = htons(_port);
		// port, htons = Host to network short converti le port dans le bon format reseau
		servAddress.sin_addr.s_addr = INADDR_ANY; 
		// accepte toute les IP
		// sin = Sockaddr INternet(adress du socket)
	if (bind(serverSocket, (struct sockaddr*)&servAddress, sizeof(servAddress)) < 0)
    	std::cout << "ERROR bind failed" << std::endl;
	// bind associe une adresse au socket
	if (listen(serverSocket, 10) < 0)
    	std::cout << "ERROR listen failed" << std::endl;
	// ce socket est pret a recevoir des connexions
	// CONFIG POLL (coeur du serv) sans poll:
	// le serv fait, accept() -> bloque attend un client
	// recv() -> bloque aussi attend des donnes
	// donc on gere que un client en meme temps poll surveille plusieurs fd's

	// analogie :
	// 	pollfd = Une ligne téléphonique
	// fd      = Numéro de la ligne (ex: ligne 5)
	// events  = "Préviens-moi si ça sonne" (POLLIN) tjr utilise POLLOUT quand send a bloque
	// revents = "La ligne 5 a sonné !" (rempli après poll())
	_serverFd = serverSocket;
	// Sauvegarde le fd du serveur dans l'attribut de classe
	// Pour pouvoir le retrouver plus tard (dans run())
	struct pollfd pfd;
	// Crée une structure pour décrire CE fd à surveiller
	pfd.fd = _serverFd;
	// "Surveille le socket serveur"
	pfd.events = POLLIN;
	// "Préviens-moi quand quelqu'un veut se connecter"
	pfd.revents = 0;
	// Initialise à 0 (poll() le remplira)
	_pollFds.push_back(pfd);
	// Ajoute au tableau des fd à surveiller
}
void Server::run()
{
	// run boucle principale
	
	// Configuration des signaux
	signal(SIGPIPE, SIG_IGN);   // Ignore SIGPIPE (évite crash si send() sur client déco)
	signal(SIGINT, signalHandler);  // Ctrl+C → shutdown propre
	signal(SIGQUIT, signalHandler); // Ctrl+\ → shutdown propre
	
	// Boucle principale - tourne tant que g_running == 1
	while (g_running)
	{
		// poll avec timeout de 1000ms pour vérifier g_running régulièrement
		int pollResult = poll(&_pollFds[0], _pollFds.size(), 1000);
		
		// Si poll a été interrompu par un signal ou timeout, on continue
		if (pollResult <= 0)
			continue;
        // Parcourir tous les fd
        for (size_t i = 0; i < _pollFds.size(); i++)
        {
            // Si ce fd a quelque chose à dire
			if (_pollFds[i].revents & POLLHUP)
			{
				    // & = bitwise AND (ET bit à bit)
    				// Vérifie si le flag POLLHUP est présent dans revents
    				// POLLHUP = client déconnecté
					// &	AND bit à bit	a & b
					// |	OR bit à bit	a | b
					// <<	Shift gauche (bit shift)	a << 2
					// >>	Shift droite (bit shift)	a >> 2
				_disconnectClient(_pollFds[i].fd);
			}
            else if (_pollFds[i].revents & POLLIN)
            {

            	if (_pollFds[i].fd == _serverFd)
            	{
            	    // Nouvelle connexion
            	    _acceptClient();
            	}
            	else
            	{
            	    // Un client envoie des données
            	    _handleClientData(_pollFds[i].fd);
            	}
            }
        }
    }	// Après la boucle = on a reçu un signal d'arrêt
	std::cout << "Server stopped." << std::endl;}
void Server::_acceptClient()
{

	int clientFd = accept(_serverFd, NULL, NULL);
	// accept peut bloquer l'appelant jusqu'à ce qu'une connexion 
	// soit présente si aucune connexion en attente n'est
	//  présente dans la file d'attente et que le socket est marqué comme bloquant
	if (clientFd < 0)
	{
	    std::cout << "ERROR accept() failed" << std::endl;
	    return;  // ← IMPORTANT ! Sinon tu fais fcntl sur fd=-1
	}
	fcntl(clientFd, F_SETFL, O_NONBLOCK);
	struct pollfd pfd;
	// Crée une structure pour décrire CE fd à surveiller
	pfd.fd = clientFd;
	// "Surveille le socket serveur"
	pfd.events = POLLIN;
	// "Préviens-moi quand quelqu'un veut se connecter"
	pfd.revents = 0;
	// Initialise à 0 (poll() le remplira)
	_pollFds.push_back(pfd);

	// Créer l'objet Client et le stocker dans la map
	Client* newClient = new Client(clientFd);
	_clients[clientFd] = newClient;

	std::cout << "New client fd = " << clientFd << std::endl;
}
void Server::_handleClientData(int fd)
{
	char buffer[512]; 
	// message limite a 512 oct
	int readBytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
		
	if (readBytes < 0)
	{
    	return;
	}
	if (readBytes == 0)
	{
        std::cout << "Client disconnected" << std::endl;
        _disconnectClient(fd);
        return;
    }
	buffer[readBytes] = '\0';
	std::cout << "Received: " << buffer << std::endl;
	
	// Récupérer le client correspondant au fd
	Client* client = getClientByFd(fd);
	if (client == NULL)
	{
		return;
	}

	// Ajouter les données reçues au buffer du client
	client->appendBuffer(buffer);

	// Parser et exécuter les commandes
	Parser::parseClientData(this, client);
}
void Server::_disconnectClient(int fd)
{
	// nettoie quand un client part

	if (_clients.find(fd) != _clients.end())
	{
		Client* client = _clients[fd];
		std::vector<Channel*> channels = client->getChannels();

		for (std::vector<Channel*>::iterator itChan = channels.begin(); itChan != channels.end(); ++itChan)
		{
			Channel* channel = *itChan;
			channel->removeClient(client);
			if (channel->isEmpty())
			{
				std::map<std::string, Channel*>::iterator itMap = _channels.find(channel->getName());
				if (itMap != _channels.end())
				{
					delete itMap->second;
					_channels.erase(itMap);
				}
			}
		}

		delete client;
		_clients.erase(fd);
	}

	close(fd);

	for (std::vector<struct pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); it++)
	{
		if (it->fd == fd)
		{
			_pollFds.erase(it);
			break;
		}
		
	}
	
}

void Server::disconnectClient(int fd)
{
	_disconnectClient(fd);
}

void Server::removeChannelIfEmpty(const std::string& name)
{
	std::map<std::string, Channel*>::iterator it = _channels.find(name);
	if (it != _channels.end() && it->second->isEmpty())
	{
		delete it->second;
		_channels.erase(it);
	}
}
void Server::sendToClient(int fd, const std::string& msg)
{

    if (send(fd, msg.c_str(), msg.length(), 0) < 0)
        std::cerr << "Error sending to fd " << fd << std::endl;
}


void Server::sendToAll(const std::string& msg, int exclude_fd)
{	
	for (std::vector<struct pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); it++)
	{
		if (it->fd != _serverFd && it->fd != exclude_fd)
		{
			sendToClient(it->fd, msg);
		}
		
	}

}


// Trouve un client par son nickname
Client* Server::getClientByNick(const std::string& nick)
{
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->second->getNickname() == nick)
			return it->second;
	}
	return NULL;  // Pas trouvé
}

// Trouve un client par son fd
Client* Server::getClientByFd(int fd)
{
	if (_clients.find(fd) != _clients.end())
		return _clients[fd];
	return NULL;
}

// Trouve un channel par son nom
Channel* Server::getChannel(const std::string& name)
{
	if (_channels.find(name) != _channels.end())
		return _channels[name];
	return NULL;
}

// Crée un channel (utilisé par JOIN si le channel n'existe pas)
Channel* Server::createChannel(const std::string& name)
{
	if (_channels.find(name) == _channels.end())
	{
		Channel* newChannel = new Channel(name);
		_channels[name] = newChannel;
		return newChannel;
	}
	return _channels[name];  // Existe déjà
}