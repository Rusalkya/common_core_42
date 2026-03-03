/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrings <akrings@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:16:55 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/23 14:04:27 by akrings          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TOPIC.cpp
** Commande IRC: TOPIC <#channel> [nouveau topic]
**
** Rôle: Voir ou modifier le sujet d'un channel
**
** Syntaxe: TOPIC <#channel>               → voir le topic
**          TOPIC <#channel> :nouveau      → changer le topic
** Exemple: TOPIC #general
**          TOPIC #general :Bienvenue !
** Réponses:
**   - 331: Pas de topic
**   - 332: Afficher le topic actuel
**   - 482: Pas OP (si channel +t)
*/

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"

/*
** Explications:
** 1. TOPIC permet de voir le topic ou de le modifier
** 2. Si pas d'argument après le channel: on affiche le topic actuel
** 3. Si un argument est fourni: on modifie le topic
** 4. Vérifications:
**    - Le client doit être dans le channel
**    - Si channel +t (topic restricted): seul un OP peut changer le topic
** 5. Réponses possible:
**    - RPL_NOTOPIC (331): pas de topic
**    - RPL_TOPIC (332): affiche le topic actuel
** 6. Format du message de changement:
**    :nick!user@host TOPIC #channel :nouveau topic
**    Envoyé à TOUS les users du channel
*/

void Parser::cmd_TOPIC(Server* server, Client* client, const std::vector<std::string>& parts)
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
			IRC::formatError(IRC::ERR_NEEDMOREPARAMS, client->getNickname(), "TOPIC :Not enough parameters"));
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
			IRC::formatError(IRC::ERR_NOTONCHANNEL, client->getNickname(), channelName + " :You're not on that channel"));
		return;
	}

	if (parts.size() == 2)
	{
		if (channel->getTopic().empty())
			server->sendToClient(client->getFd(),
				IRC::formatReply(IRC::RPL_NOTOPIC, client->getNickname(), channelName + " :No topic is set"));
		else
			server->sendToClient(client->getFd(),
				IRC::formatReply(IRC::RPL_TOPIC, client->getNickname(), channelName + " :" + channel->getTopic()));
		return;
	}

	if (channel->isTopicRestricted() && !channel->isOperator(client))
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_CHANOPRIVSNEEDED, client->getNickname(), channelName + " :You're not channel operator"));
		return;
	}

	channel->setTopic(parts[2]);
	std::string topicMsg = ":" + client->getPrefix() + " TOPIC " + channelName + " :" + channel->getTopic() + "\r\n";
	std::vector<Client*>& members = channel->getClients();
	for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); ++it)
		server->sendToClient((*it)->getFd(), topicMsg);
}
