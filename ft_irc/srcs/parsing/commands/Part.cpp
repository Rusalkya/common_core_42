/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrings <akrings@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 14:01:06 by akrings           #+#    #+#             */
/*   Updated: 2026/02/23 14:02:34 by akrings          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"

/*
** PART: Quitter un channel
**
** Syntaxe: PART <#channel> [:reason]
*/

void Parser::cmd_PART(Server* server, Client* client, const std::vector<std::string>& parts)
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
			IRC::formatError(IRC::ERR_NEEDMOREPARAMS, client->getNickname(), "PART :Not enough parameters"));
		return;
	}

	std::string channelName = parts[1];
	Channel* channel = server->getChannel(channelName);
	if (channel == NULL)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOSUCHCHANNEL, client->getNickname(), ":No such channel"));
		return;
	}
	if (!channel->isInChannel(client))
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOTONCHANNEL, client->getNickname(), ":You're not on that channel"));
		return;
	}

	std::string reason = (parts.size() > 2) ? parts[2] : client->getNickname();
	std::string partMsg = ":" + client->getPrefix() + " PART " + channelName + " :" + reason + "\r\n";
	std::vector<Client*>& members = channel->getClients();
	for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); ++it)
		server->sendToClient((*it)->getFd(), partMsg);

	channel->removeClient(client);
	client->removeChannel(channel);
	server->removeChannelIfEmpty(channelName);
}
