/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrings <akrings@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:03:23 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/23 14:03:28 by akrings          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** QUIT.cpp
** Commande IRC: QUIT [message]
**
** Rôle: Déconnexion propre du client
**
** Syntaxe: QUIT [message]
** Exemple: QUIT :À plus tard !
**          QUIT
*/

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"

/*
** Explications:
** 1. QUIT permet au client de se déconnecter proprement
** 2. Avant de fermer la connexion, notifier tous les channels
** 3. Annoncer le départ dans chaque channel où le client était
** 4. Format de la notification:
**    :nick!user@host QUIT :message de départ
** 5. Puis fermer la connexion
**
** Processus:
** - Parser le message de départ (optionnel)
** - Récupérer tous les channels du client
** - Pour chaque channel:
**   * Envoyer la notification à tous les users du channel
**   * Retirer le client du channel
**   * Si le channel est vide: le supprimer
** - Fermer la connexion du client
*/

void Parser::cmd_QUIT(Server* server, Client* client, const std::vector<std::string>& parts)
{
	std::string reason = "Client Quit";
	if (parts.size() > 1)
		reason = parts[1];

	std::string quitMsg = ":" + client->getPrefix() + " QUIT :" + reason + "\r\n";
	std::vector<Channel*> channels = client->getChannels();
	for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		std::vector<Client*>& members = (*it)->getClients();
		for (std::vector<Client*>::iterator itMember = members.begin(); itMember != members.end(); ++itMember)
		{
			if ((*itMember)->getFd() != client->getFd())
				server->sendToClient((*itMember)->getFd(), quitMsg);
		}
	}
	server->disconnectClient(client->getFd());
}
