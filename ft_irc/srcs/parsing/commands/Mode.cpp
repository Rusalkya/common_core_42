/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtohami- <wtohami-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:24:46 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/24 14:39:25 by wtohami-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** MODE.cpp
** Commande IRC: MODE <#channel> <+/-mode> [paramètre]
**
** Rôle: Changer les modes d'un channel (OP seulement)
**
** Syntaxe: MODE <#channel> <+/-mode> [paramètre]
** Exemples: MODE #general +i                 → invite only ON
**           MODE #general -i                 → invite only OFF
**           MODE #general +k secretpass      → ajouter password
**           MODE #general -k                 → retirer password
**           MODE #general +l 10              → limite 10 users
**           MODE #general +o bob             → bob devient op
**           MODE #general -o bob             → bob n'est plus op
*/

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"
#include <cctype>  // isdigit()
#include <cstdlib> // strtoul()

/*
** Explications:
** 1. MODE permet de changer les modes d'un channel
** 2. Seul un OP peut utiliser MODE
** 3. Modes RFC 1459:
**    +i (invite only): seuls les invités peuvent joindre
**    +t (topic restricted): seuls les OPs peuvent changer le topic
**    +k (password): channel protégé par password
**    +o (operator): donner/retirer les pouvoirs d'OP
**    +l (limit): limiter le nombre de personnes
** 4. Format: MODE <channel> <[+-]mode> [paramètre]
**    - "+i": invite only activé
**    - "-i": invite only désactivé
**    - "+k password": ajouter password
**    - "+o nick": rendre nick opérateur
** 5. Le "+" est obligatoire mais peut être omis (par défaut "+")
** 6. Envoyer le changement à TOUS les users du channel
*/

void Parser::cmd_MODE(Server* server, Client* client, const std::vector<std::string>& parts)
{
	if (!client->isRegistered())
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOTREGISTERED, "*", ":You have not registered"));
		return;
	}
	if (parts.size() <= 2)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NEEDMOREPARAMS, client->getNickname(), "MODE :Not enough parameters"));
		return;
	}

	std::string target = parts[1];
	if (target.empty() || target[0] != '#')
		return;

	Channel* channel = server->getChannel(target);
	if (channel == NULL)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOSUCHCHANNEL, client->getNickname(), ":No such channel"));
		return;
	}

	if (!channel->isOperator(client))
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_CHANOPRIVSNEEDED, client->getNickname(), target + " :You're not channel operator"));
		return;
	}

	std::string mode = parts[2];
	bool adding = true;
	size_t paramIndex = 3;
	size_t i = 0;
	if (mode[i] == '+' || mode[i] == '-')
	{
		if (mode[i] == '-')
			adding = false;
		i++;
	}
	if (mode[i] == 'i')
		channel->setInviteOnly(adding);
	else if (mode[i] == 't')
		channel->setTopicRestricted(adding);
	else if (mode[i] == 'k')
	{
		if (adding)
		{
			if (paramIndex < parts.size())
				channel->setPassword(parts[paramIndex++]);
		}
		else
			channel->setPassword("");
	}
	else if (mode[i] == 'l')
	{
		if (adding)
		{
			if (paramIndex < parts.size())
				channel->setUserLimit(static_cast<size_t>(std::atoi(parts[paramIndex++].c_str())));
		}
		else
			channel->setUserLimit(0);
	}
	else if (mode[i] == 'o')
	{
		if (paramIndex < parts.size())
		{
			Client* targetClient = server->getClientByNick(parts[paramIndex++]);
			if (targetClient != NULL && channel->isInChannel(targetClient))
			{
				if (adding)
					channel->addOperator(targetClient);
				else
					channel->removeOperator(targetClient);
			}
		}
	}
	std::string modeMsg = ":" + client->getPrefix() + " MODE " + target + " " + mode;
	for (size_t i = 3; i < paramIndex && i < parts.size(); ++i)
		modeMsg += " " + parts[i];
	modeMsg += "\r\n";

	std::vector<Client*>& members = channel->getClients();
	for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); ++it)
		server->sendToClient((*it)->getFd(), modeMsg);
}
