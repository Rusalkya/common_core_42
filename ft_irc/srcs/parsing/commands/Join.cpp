/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtohami- <wtohami-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:20:59 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/24 13:19:48 by wtohami-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"

/*
** Explications:
** 1. Un channel commence TOUJOURS par # ou &
**    #general = channel public
**    &secret = channel privé
** 2. Si le channel n'existe pas: on le crée, le client devient OP
** 3. Si le channel existe: on vérifie les modes
**    - +i (invite only): client doit être dans la liste _invited
**    - +k (password): doit matcher le password du channel
**    - +l (limite): vérifier si la limite d'utilisateurs est atteinte
** 4. Ajouter le client au channel
** 5. Envoyer à TOUS les users du channel (y compris le nouveau):
**    :nick!user@host JOIN :#channel
** 6. Envoyer le topic du channel au client (si existe)
** 7. Envoyer la liste des users du channel au client (RPL_NAMREPLY)
*/

void Parser::cmd_JOIN(Server* server, Client* client, const std::vector<std::string>& parts)
{
	if (!client->isRegistered())
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOTREGISTERED, "*", ":You have not registered"));
		return;
	}

	if (parts.size() < 2)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NEEDMOREPARAMS, client->getNickname(), "JOIN :Not enough parameters"));
		return;
	}

	std::string channelName = parts[1];
	std::string password = (parts.size() > 2) ? parts[2] : "";

	if (channelName.empty() || channelName[0] != '#')
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOSUCHCHANNEL, client->getNickname(), ":Invalid channel"));
		return;
	}

	Channel* channel = server->getChannel(channelName);
	bool created = false;
	if (channel == NULL)
	{
		channel = server->createChannel(channelName);
		created = true;
	}

	if (channel->isInChannel(client))
		return;

	if (!created)
	{
		if (channel->isInviteOnly() && !channel->isInvited(client))
		{
			server->sendToClient(client->getFd(),
				IRC::formatError(IRC::ERR_INVITEONLYCHAN, client->getNickname(), ":Cannot join channel (+i)"));
			return;
		}
		if (!channel->getPassword().empty() && password != channel->getPassword())
		{
			server->sendToClient(client->getFd(),
				IRC::formatError(IRC::ERR_BADCHANNELKEY, client->getNickname(), ":Bad channel key"));
			return;
		}
		if (channel->getUserLimit() > 0 && channel->getClientCount() >= channel->getUserLimit())
		{
			server->sendToClient(client->getFd(),
				IRC::formatError(IRC::ERR_CHANNELISFULL, client->getNickname(), ":Channel is full"));
			return;
		}
	}

	channel->addClient(client);
	client->addChannel(channel);
	if (created)
		channel->addOperator(client);

	std::string joinMsg = ":" + client->getPrefix() + " JOIN :" + channelName + "\r\n";
	std::vector<Client*>& members = channel->getClients();
	for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); ++it)
		server->sendToClient((*it)->getFd(), joinMsg);

	if (channel->getTopic().empty())
		server->sendToClient(client->getFd(),
			IRC::formatReply(IRC::RPL_NOTOPIC, client->getNickname(), channelName + " :No topic is set"));
	else
		server->sendToClient(client->getFd(),
			IRC::formatReply(IRC::RPL_TOPIC, client->getNickname(), channelName + " :" + channel->getTopic()));

	std::string names;
	for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); ++it)
	{
		if (channel->isOperator(*it))
			names += "@";
		names += (*it)->getNickname();
		names += " ";
	}
	server->sendToClient(client->getFd(),
		IRC::formatReply(IRC::RPL_NAMREPLY, client->getNickname(), "= " + channelName + " :" + names));
	server->sendToClient(client->getFd(),
		IRC::formatReply(IRC::RPL_ENDOFNAMES, client->getNickname(), channelName + " :End of /NAMES list"));
}
