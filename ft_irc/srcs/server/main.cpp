#include "../../includes/Server.hpp"
#include <iostream>
#include <cstdlib> 


int main(int argc, char **argv)
{
	// Le serveur a besoin de 2 arguments:
	// - port: sur quel port écouter (ex: 6667)
	// - password: mot de passe pour se connecter
	if (argc != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}
	// "6667" → 6667
	int port = std::atoi(argv[1]);
	
	// Validation du port (doit être entre 1 et 65535)
	// Ports < 1024 nécessitent les droits root
	if (port <= 0 || port > 65535)
	{
		std::cerr << "Error: Invalid port number (must be 1-65535)" << std::endl;
		return 1;
	}
	
	std::string password = argv[2];
	
	// Validation du password (non vide)
	if (password.empty())
	{
		std::cerr << "Error: Password cannot be empty" << std::endl;
		return 1;
	}

	// 3. CRÉATION ET LANCEMENT DU SERVEUR
	std::cout << "Creating server on port " << port << "..." << std::endl;
	
	// Le constructeur:
	// - Crée le socket
	// - Configure SO_REUSEADDR
	// - bind() sur le port
	// - listen() pour accepter les connexions
	// - Ajoute le socket au poll()
	Server server(port, password);
	
	std::cout << "Server initialized successfully!" << std::endl;
	std::cout << "Waiting for connections..." << std::endl;

	// run() = boucle infinie qui:
	// - poll() attend les événements
	// - Accepte les nouvelles connexions
	// - Reçoit les messages des clients
	// - Gère les déconnexions
	server.run();
	// On n'arrive jamais ici (boucle infinie)
	// Sauf si on ajoute une gestion de signal (SIGINT) plus tard
	return 0;
}