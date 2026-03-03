#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <cstddef>

class Client;

class Channel {

	private:
		std::string				_name;
		std::string				_topic;
		std::string				_password;
		size_t					_userLimit;
		bool					_inviteOnly;
		bool					_topicRestricted;
		std::vector<Client*>	_clients;
		std::vector<Client*>	_operators;
		std::vector<Client*>	_invited;

	public:
		Channel(const std::string& name);
		Channel(const Channel& other);
		Channel& operator=(const Channel& other);
		~Channel();

		std::string getName() const;
		std::string getTopic() const;
		std::string getPassword() const;
		size_t getUserLimit() const;
		bool isInviteOnly() const;
		bool isTopicRestricted() const;
		std::vector<Client*>& getClients();
		std::vector<Client*>& getOperators();

		void setTopic(const std::string& topic);
		void setPassword(const std::string& password);
		void setUserLimit(size_t limit);
		void setInviteOnly(bool inviteOnly);
		void setTopicRestricted(bool restricted);

		void addClient(Client* client);
		void removeClient(Client* client);
		bool isInChannel(Client* client) const;

		void addOperator(Client* client);
		void removeOperator(Client* client);
		bool isOperator(Client* client) const;

		void addInvited(Client* client);
		void removeInvited(Client* client);
		bool isInvited(Client* client) const;

		bool isEmpty() const;
		size_t getClientCount() const;

};

#endif