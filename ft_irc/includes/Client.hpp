

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <sys/socket.h>    // socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h>    // struct sockaddr_in, htons()
#include <arpa/inet.h>     // inet_ntoa(), inet_addr()
#include <unistd.h>        // close()
#include <fcntl.h>         // fcntl(), O_NONBLOCK
#include <poll.h>          // poll(), struct pollfd
#include <csignal>         // signal(), SIGPIPE
#include <iostream>
#include <vector>
#include <map>
#include <string>

class Channel;

class Client {
	
	private:
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
		std::string _buffer;		
		bool _authenticated; 
		bool _registered;
		std::vector<Channel*> _channels; 
	public:
		Client(int fd);
		Client(const Client& other);
		Client& operator=(const Client& other);
		~Client();
		int getFd();
		std::string getNickname();
		std::string getUsername();
		std::string getRealname();
		std::string getHostname();
		bool isAuthenticated();
		bool isRegistered();
		std::string& getBuffer();
		std::vector<Channel*>& getChannels();

		void setNickname(const std::string& nick);
		void setUsername(const std::string& user);
		void setRealname(const std::string& real);
		void setHostname(const std::string& host);
		void setAuthenticated(bool auth);
		void setRegistered(bool reg);
		
		void appendBuffer(const std::string& data);  // Ajoute au buffer
		void clearBuffer();                       	// Vide le buffer
		void addChannel(Channel* channel);            // Ajoute un channel
		void removeChannel(Channel* channel);         // Retire un channel
		std::string getPrefix() const;               // Retourne "nick!user@host"
};
#endif
