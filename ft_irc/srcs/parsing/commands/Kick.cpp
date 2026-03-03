/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrings <akrings@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:22:49 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/23 14:03:45 by akrings          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"

/*
** Explications:
** 1. KICK permet à un OP d'expulser quelqu'un d'un channel
** 2. Seul un OP peut utiliser KICK
** 3. On doit vérifier que:
**    - Le sender est OP du channel
**    - La cible existe et est dans le channel
** 4. Format du message envoyé:
**    :nick!user@host KICK #channel target :raison
** 5. Le message est envoyé à TOUS les users du channel y compris la cible
**    (pour qu'elle sache pourquoi elle a été kickée)
** 6. Puis on retire la cible du channel
*/

void Parser::cmd_KICK(Server* server, Client* client, const std::vector<std::string>& parts)
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
			IRC::formatError(IRC::ERR_NEEDMOREPARAMS, client->getNickname(), "KICK :Not enough parameters"));
		return;
	}

	std::string channelName = parts[1];
	std::string targetNick = parts[2];
	std::string reason = (parts.size() > 3) ? parts[3] : client->getNickname();

	Channel* channel = server->getChannel(channelName);
	if (channel == NULL)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOSUCHCHANNEL, client->getNickname(), ":No such channel"));
		return;
	}
	if (!channel->isOperator(client))
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_CHANOPRIVSNEEDED, client->getNickname(), channelName + " :You're not channel operator"));
		return;
	}

	Client* targetClient = server->getClientByNick(targetNick);
	if (targetClient == NULL || !channel->isInChannel(targetClient))
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_USERNOTINCHANNEL, client->getNickname(), targetNick + " " + channelName + " :They aren't on that channel"));
		return;
	}

	std::string kickMsg = ":" + client->getPrefix() + " KICK " + channelName + " " + targetNick + " :" + reason + "\r\n";
	std::vector<Client*>& members = channel->getClients();
	for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); ++it)
		server->sendToClient((*it)->getFd(), kickMsg);

	channel->removeClient(targetClient);
	targetClient->removeChannel(channel);
}
