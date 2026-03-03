#include "../../includes/Client.hpp"

Client::Client(int fd)
	: _fd(fd), _nickname(""), _username(""), _realname(""), _hostname(""),
	  _buffer(""), _authenticated(false), _registered(false)
{

}

int Client::getFd()
{
	return _fd;
}

std::string Client::getNickname()
{
	return _nickname;
}

std::string Client::getUsername()
{
	return _username;
}

std::string Client::getRealname()
{
	return _realname;
}

std::string Client::getHostname()
{
	return _hostname;
}

bool Client::isAuthenticated()
{
    return _authenticated;
}

bool Client::isRegistered()
{
    return _registered;
}

std::string& Client::getBuffer()
{
    return _buffer;
}

void Client::setNickname(const std::string& nick)
{
	_nickname = nick;
}

void Client::setUsername(const std::string& user)
{
	_username = user;
}

void Client::setRealname(const std::string& real)
{
	_realname = real;
}

void Client::setHostname(const std::string& host)
{
	_hostname = host;
}

void Client::setAuthenticated(bool auth)
{
	_authenticated = auth;
}

void Client::setRegistered(bool reg)
{
	_registered = reg;
}

void Client::appendBuffer(const std::string& data)
{
	_buffer += data;
}

void Client::clearBuffer()
{
	_buffer.clear();
}

std::vector<Channel*>& Client::getChannels()
{
	return _channels;
}

void Client::addChannel(Channel* channel)
{
	_channels.push_back(channel);
}

void Client::removeChannel(Channel* channel)
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (_channels[i] == channel)
		{
			_channels.erase(_channels.begin() + i);
			return;
		}
	}
}

std::string Client::getPrefix() const
{
	return _nickname + "!" + _username + "@localhost";
}

// Orthodox Canonical Form
Client::~Client()
{
}

Client::Client(const Client& other)
	: _fd(other._fd), _nickname(other._nickname), _username(other._username),
	  _realname(other._realname), _hostname(other._hostname), _buffer(other._buffer),
	  _authenticated(other._authenticated), _registered(other._registered), _channels(other._channels)
{
}

Client& Client::operator=(const Client& other)
{
	if (this != &other)
	{
		_fd = other._fd;
		_nickname = other._nickname;
		_username = other._username;
		_realname = other._realname;
		_authenticated = other._authenticated;
		_registered = other._registered;
		_buffer = other._buffer;
		_channels = other._channels;
	}
	return *this;
}
