#include "../../includes/Channel.hpp"
#include "../../includes/Client.hpp"
#include <algorithm>

Channel::Channel(const std::string& name)
	: _name(name), _topic(""), _password(""), _userLimit(0),
	  _inviteOnly(false), _topicRestricted(false)
{
}

Channel::Channel(const Channel& other)
	: _name(other._name), _topic(other._topic), _password(other._password),
	  _userLimit(other._userLimit), _inviteOnly(other._inviteOnly),
	  _topicRestricted(other._topicRestricted), _clients(other._clients),
	  _operators(other._operators), _invited(other._invited)
{
}

Channel& Channel::operator=(const Channel& other)
{
	if (this != &other)
	{
		_name = other._name;
		_topic = other._topic;
		_password = other._password;
		_userLimit = other._userLimit;
		_inviteOnly = other._inviteOnly;
		_topicRestricted = other._topicRestricted;
		_clients = other._clients;
		_operators = other._operators;
		_invited = other._invited;
	}
	return *this;
}

Channel::~Channel()
{
}


std::string Channel::getName() const
{
	return _name;
}

std::string Channel::getTopic() const
{
	return _topic;
}

std::string Channel::getPassword() const
{
	return _password;
}

size_t Channel::getUserLimit() const
{
	return _userLimit;
}

bool Channel::isInviteOnly() const
{
	return _inviteOnly;
}

bool Channel::isTopicRestricted() const
{
	return _topicRestricted;
}

std::vector<Client*>& Channel::getClients()
{
	return _clients;
}

std::vector<Client*>& Channel::getOperators()
{
	return _operators;
}


void Channel::setTopic(const std::string& topic)
{
	_topic = topic;
}

void Channel::setPassword(const std::string& password)
{
	_password = password;
}

void Channel::setUserLimit(size_t limit)
{
	_userLimit = limit;
}

void Channel::setInviteOnly(bool inviteOnly)
{
	_inviteOnly = inviteOnly;
}

void Channel::setTopicRestricted(bool restricted)
{
	_topicRestricted = restricted;
}


void Channel::addClient(Client* client)
{
	if (!isInChannel(client))
		_clients.push_back(client);
}

void Channel::removeClient(Client* client)
{
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end())
		_clients.erase(it);
	removeOperator(client);
	removeInvited(client);
}

bool Channel::isInChannel(Client* client) const
{
	return std::find(_clients.begin(), _clients.end(), client) != _clients.end();
}


void Channel::addOperator(Client* client)
{
	if (!isOperator(client))
		_operators.push_back(client);
}

void Channel::removeOperator(Client* client)
{
	std::vector<Client*>::iterator it = std::find(_operators.begin(), _operators.end(), client);
	if (it != _operators.end())
		_operators.erase(it);
}

bool Channel::isOperator(Client* client) const
{
	return std::find(_operators.begin(), _operators.end(), client) != _operators.end();
}


void Channel::addInvited(Client* client)
{
	if (!isInvited(client))
		_invited.push_back(client);
}

void Channel::removeInvited(Client* client)
{
	std::vector<Client*>::iterator it = std::find(_invited.begin(), _invited.end(), client);
	if (it != _invited.end())
		_invited.erase(it);
}

bool Channel::isInvited(Client* client) const
{
	return std::find(_invited.begin(), _invited.end(), client) != _invited.end();
}


bool Channel::isEmpty() const
{
	return _clients.empty();
}

size_t Channel::getClientCount() const
{
	return _clients.size();
}
