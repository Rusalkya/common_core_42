/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrings <akrings@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:16:28 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/23 14:04:07 by akrings          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"

/*
** INVITE: Inviter quelqu'un sur un channel
**
** Syntaxe: INVITE <nick> <#channel>
*/
void Parser::cmd_INVITE(Server* server, Client* client, const std::vector<std::string>& parts)
{
	if (!client->isRegistered())
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOTREGISTERED, "*", ":You have not registered"));
		return;
	}
	if (parts.size() < 3)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NEEDMOREPARAMS, client->getNickname(), "INVITE :Not enough parameters"));
		return;
	}

	std::string targetNick = parts[1];
	std::string channelName = parts[2];
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
			IRC::formatError(IRC::ERR_NOTONCHANNEL, client->getNickname(), channelName + " :You're not on that channel"));
		return;
	}
	if (channel->isInviteOnly() && !channel->isOperator(client))
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_CHANOPRIVSNEEDED, client->getNickname(), channelName + " :You're not channel operator"));
		return;
	}

	Client* targetClient = server->getClientByNick(targetNick);
	if (targetClient == NULL)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOSUCHNICK, client->getNickname(), targetNick + " :No such nick"));
		return;
	}
	if (channel->isInChannel(targetClient))
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_USERONCHANNEL, client->getNickname(), targetNick + " " + channelName + " :is already on channel"));
		return;
	}

	channel->addInvited(targetClient);
	server->sendToClient(client->getFd(),
		IRC::formatReply(IRC::RPL_INVITING, client->getNickname(), targetNick + " " + channelName));
	server->sendToClient(targetClient->getFd(),
		":" + client->getPrefix() + " INVITE " + targetNick + " :" + channelName + "\r\n");
}
