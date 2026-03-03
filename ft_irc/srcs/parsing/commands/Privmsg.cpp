/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtohami- <wtohami-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:03:14 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/24 13:20:13 by wtohami-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** PRIVMSG.cpp
** Commande IRC: PRIVMSG <cible> :<message>
**
** Rôle: Envoyer un message à un channel ou un user
**
** Syntaxe: PRIVMSG <cible> :<message>
** Exemple: PRIVMSG #general :Salut tout le monde !
**          PRIVMSG bob :Hey, ça va ?
** Réponses:
**   - 451: Client non enregistré
**   - 411: Pas de destinataire
**   - 412: Pas de texte à envoyer
**   - 401: Nick inexistant
**   - 403: Channel inexistant
*/

#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"

/*
** Explications:
** 1. PRIVMSG envoie un message PUBLIC (à un channel) ou PRIVÉ (à un user)
** 2. Format du message reçu:
**    PRIVMSG <cible> :<message>
**    - <cible> commence par # ou & → channel
**    - <cible> est un nickname → message privé
** 3. Pour un channel:
**    - Vérifier que le channel existe
**    - Vérifier que le client est dans le channel
**    - Envoyer le message à TOUS les users du channel SAUF l'envoyeur
** 4. Pour un user:
**    - Trouver le user par nickname
**    - Envoyer directement
** 5. Le message envoyé commence par le PRÉFIXE du client:
**    :nick!user@host PRIVMSG <cible> :<message>\r\n
*/

void Parser::cmd_PRIVMSG(Server* server, Client* client, const std::vector<std::string>& parts)
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
			IRC::formatError(IRC::ERR_NORECIPIENT, client->getNickname(), ":No recipient given (PRIVMSG)"));
		return;
	}
	if (parts.size() < 3 || parts[2].empty())
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOTEXTTOSEND, client->getNickname(), ":No text to send"));
		return;
	}

	std::string target = parts[1];
	std::string message = parts[2];
	std::string fullMsg = ":" + client->getPrefix() + " PRIVMSG " + target + " :" + message + "\r\n";

	if (!target.empty() && target[0] == '#')
	{
		Channel* channel = server->getChannel(target);
		if (channel == NULL)
		{
			server->sendToClient(client->getFd(),
				IRC::formatError(IRC::ERR_NOSUCHCHANNEL, client->getNickname(), ":No such channel"));
			return;
		}
		if (!channel->isInChannel(client))
		{
			server->sendToClient(client->getFd(),
				IRC::formatError(IRC::ERR_NOTONCHANNEL, client->getNickname(), ":Cannot send to channel"));
			return;
		}
		std::vector<Client*>& members = channel->getClients();
		for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); ++it)
		{
			if ((*it)->getFd() != client->getFd())
				server->sendToClient((*it)->getFd(), fullMsg);
		}
		return;
	}

	Client* targetClient = server->getClientByNick(target);
	if (targetClient == NULL)
	{
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_NOSUCHNICK, client->getNickname(), ":No such nick/channel"));
		return;
	}
	server->sendToClient(targetClient->getFd(), fullMsg);
}
