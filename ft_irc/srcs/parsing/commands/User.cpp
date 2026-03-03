/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrings <akrings@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:35:05 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/23 16:19:27 by akrings          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** USER.cpp
** Commande IRC: USER <username> <mode> <unused> :<realname>
**
** Rôle: Complète l'enregistrement du client (après PASS et NICK)
**
** Syntaxe: USER <username> <mode> <unused> :<realname>
** Exemple: USER bob 0 * :Bob Le Bricoleur
** Réponses:
**   - 451: Client non enregistré (pas de PASS/NICK d'abord)
**   - 462: Déjà enregistré
**   - 001: Bienvenue (RPL_WELCOME)
*/

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "NumericReplies.hpp"

/*
** Explications:
** 1. USER doit être envoyé APRÈS PASS et NICK
** 2. Format: USER <username> <mode> <unused> :<realname>
**    - <username>: identité Unix du client (login)
**    - <mode>: bits de mode utilisateur (ignoré, généralement "0")
**    - <unused>: champ inutilisé (généralement "*")
**    - <realname>: nom réel du client (peut avoir des espaces, après ":")
** 3. Si tout est valide, le client devient "registered" et reçoit:
**    - RPL_WELCOME (001): Message de bienvenue
**    - RPL_YOURHOST (002): Info sur le serveur
**    - RPL_CREATED (003): Date de création
**
** Protocole d'enregistrement:
**   PASS <mdp>  → client.authenticated = true
**   NICK <nick> → client.nickname = nick
**   USER <...>  → client.username/realname set, client.registered = true
**   → Envoyer les messages de bienvenue
*/

void Parser::cmd_USER(Server* server, Client* client, const std::vector<std::string>& parts)
{
	if (client->isRegistered())
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_ALREADYREGISTRED, client->getNickname(), "USER :Already registered"));
		return;
	}
	// Vérifier qu'on a tous les paramètres
	if (parts.size() < 5)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NEEDMOREPARAMS, client->getNickname(), "USER :Not enough parameters"));
		return;
	}
	if (client->getNickname().empty())
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NONICKNAMEGIVEN, "*", " :No nickname given"));
		return;
	}
	std::string username = parts[1];
	std::string realname = parts[4];  // Après le ":"

	client->setUsername(username);
	client->setRealname(realname);
	client->setHostname("localhost");

	// Définir comme enregistré une fois NICK et USER sont définis
	client->setRegistered(true);
	server->sendToClient(client->getFd(),
		IRC::formatReply(IRC::RPL_WELCOME, client->getNickname(), ":Welcome to the IRC Network"));
	std::cout << "✓ Client registered: " << client->getNickname() << " (" << username << ")" << std::endl;
}
