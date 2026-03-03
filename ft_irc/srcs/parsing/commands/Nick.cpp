/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrings <akrings@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:40:19 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/23 16:15:11 by akrings          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "NumericReplies.hpp"

/*
** Explications:
** 1. Le client envoie: NICK alice\r\n
** 2. On vérifie la syntaxe et la validité du nickname
** 3. On vérifie que ce nickname n'est pas déjà utilisé par un autre client
** 4. Si valide: on met à jour le nickname du client
** 5. Si le client est maintenant complètement enregistré (NICK + USER + AUTH)
**    on envoie les messages de bienvenue
**
** Validité d'un nick IRC:
**   - Doit commencer par une lettre ou underscore
**   - Peut contenir alphanumériques, underscores, hyphens
**   - Pas d'espaces ni caractères spéciaux
**   - Généralement 1 à 9 caractères
*/

void Parser::cmd_NICK(Server* server, Client* client, const std::vector<std::string>& parts)
{
	std::string target = client->getNickname().empty() ? "*" : client->getNickname();

	if (!client->isAuthenticated())
	{
		server->sendToClient(client->getFd(),
			"Not authenticated\r\n");
		return;
	}
	// Vérifier qu'un nickname a été fourni
	if (parts.size() < 2 || parts[1].empty())
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NONICKNAMEGIVEN, target, ":No nickname given"));
		return;
	}

	std::string newNick = parts[1];

	// Vérifier les caractères valides (pas de # au début, pas d'espaces, etc.)
	if (newNick.empty() || newNick[0] == '#' || newNick.find(' ') != std::string::npos)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_ERRONEUSNICKNAME, target, newNick + " :Erroneous nickname"));
		return;
	}

	// Vérifier que le nick n'est pas déjà pris
	Client* existing = server->getClientByNick(newNick);
	if (existing != NULL && existing != client)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NICKNAMEINUSE, target, newNick + " :Nickname is already in use"));
		return;
	}

	// Tout est OK, changer le pseudo
	std::string oldNick = client->getNickname();
	client->setNickname(newNick);
	std::cout << "✓ Nick changed: " << oldNick << " → " << newNick << std::endl;
}
