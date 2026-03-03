/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrings <akrings@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:28:23 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/23 16:23:59 by akrings          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "NumericReplies.hpp"

/*
** Explications:
** 1. Le client se connecte et envoie: PASS monMotDePasse\r\n
** 2. On vérifie que le client n'est pas déjà enregistré
** 3. On compare le mot de passe fourni avec celui du serveur
** 4. Si correct: on marque le client comme authentifié
** 5. Si incorrect: on envoie l'erreur 464 et on ferme la connexion
**
** Protocole IRC:
**   - PASS doit être envoyé AVANT USER et NICK
**   - Si un client envoie USER sans PASS correct, il ne peut pas se connecter
*/

void Parser::cmd_PASS(Server* server, Client* client, const std::vector<std::string>& parts)
{
	if (client->isAuthenticated())
	{
		server->sendToClient(client->getFd(), "PASS :Already authenticated\r\n");
		return;
	}
	// Vérifier qu'il y a un password fourni
	if (parts.size() < 2)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NEEDMOREPARAMS, "*", "PASS :Not enough parameters"));
		return;
	}

	// Comparer avec le password du serveur
	if (parts[1] == server->getPassword())
	{
		client->setAuthenticated(true);
		std::cout << "✓ Client authenticated" << std::endl;
	}
	else
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_PASSWDMISMATCH, "*", ":Password incorrect"));
		std::cout << "✗ Client auth failed (wrong password)" << std::endl;
	}
}
