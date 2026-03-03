#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

class Server;
class Client;


class Parser
{
public:
	Parser();
	~Parser();

	// fonction decoupe le buffer par \r\n et traite chaque commande
	static void parseClientData(Server* server, Client* client);

private:
	// Parser une ligne de commande IRC
	// Retourne un vecteur: [COMMANDE, arg1, arg2, ...]
	static std::vector<std::string> parseLine(const std::string& line);

	// Router la commande vers la bonne fonction d'exécution
	// Retourne true si le client a été déconnecté (QUIT)
	static bool executeCommand(Server* server, Client* client, 
	                           const std::vector<std::string>& parts);

	static void cmd_PASS(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_NICK(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_USER(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_JOIN(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_PART(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_PRIVMSG(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_QUIT(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_KICK(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_INVITE(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_TOPIC(Server* server, Client* client, const std::vector<std::string>& parts);
	static void cmd_MODE(Server* server, Client* client, const std::vector<std::string>& parts);
};

#endif
