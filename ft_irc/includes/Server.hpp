
#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>    // socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h>    // struct sockaddr_in, htons()
#include <arpa/inet.h>     // inet_ntoa(), inet_addr()
#include <unistd.h>        // close()
#include <fcntl.h>         // fcntl(), O_NONBLOCK
#include <poll.h>          // poll(), struct pollfd
#include <csignal>         // signal(), SIGPIPE

#include <vector>
#include <map>
#include <string>

class Client;
class Channel;
class Parser;

class Server
{
private:
    int                         _serverFd;      // Socket d'écoute
    int                         _port;
    std::string                 _password;
    std::vector<struct pollfd>  _pollFds;       // Tableau pour poll()
    
    // Maps pour stocker les clients et channels
    std::map<int, Client*>          _clients;    // fd → Client
    std::map<std::string, Channel*> _channels;   // nom → Channel

    // Méthodes privées 
    void    _initSocket();
    void    _acceptClient();
    void    _handleClientData(int fd);
    void    _disconnectClient(int fd);

public:
    Server(int port, const std::string& password);
    ~Server();

    Server(const Server& other);
    Server& operator=(const Server& other);

    // Méthode principale
    void    run();  // La boucle poll()

    // Getters
    const std::string&  getPassword() const;
    int                 getPort() const;


    // Envoyer un message à UN client
    void    sendToClient(int fd, const std::string& msg);
    
    // Envoyer à TOUS les clients (sauf exclude_fd, mettre -1 pour envoyer à tous)
    void    sendToAll(const std::string& msg, int exclude_fd);

    // Déconnecter proprement un client
    void    disconnectClient(int fd);

    // Supprimer un channel s'il est vide
    void    removeChannelIfEmpty(const std::string& name);

    // Getters pour récupérer clients/channels
    Client*   getClientByNick(const std::string& nick);
    Client*   getClientByFd(int fd);
    Channel*  getChannel(const std::string& name);
    Channel*  createChannel(const std::string& name);
};

#endif