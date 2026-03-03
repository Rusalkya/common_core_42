/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtohami- <wtohami-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:33:47 by clfouger          #+#    #+#             */
/*   Updated: 2026/02/24 13:49:56 by wtohami-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                              PARSER                                        */
/* ************************************************************************** */
/*
** ROLE: Point d'entrée du parsing. Reçoit les données brutes du serveur.
**
** CE QUE VOUS DEVEZ FAIRE:
** 1. Recevoir le buffer du client (peut contenir plusieurs commandes)
** 2. Découper par "\r\n" (fin de commande IRC)
** 3. Pour chaque commande, extraire: COMMANDE arg1 arg2 :texte
** 4. Appeler la bonne fonction (NICK, JOIN, PRIVMSG, etc.)
**
** EXEMPLE D'INPUT:
**   "NICK bob\r\nJOIN #general\r\n"
**   → Commande 1: NICK avec arg "bob"
**   → Commande 2: JOIN avec arg "#general"
**
** MÉTHODES UTILES DU SERVEUR:
**   server.getClientByFd(fd)     → récupère le Client* qui a envoyé
**   server.getClientByNick(nick) → trouve un client par pseudo
**   server.getChannel(name)      → trouve un channel
**   server.createChannel(name)   → crée un channel
**   server.sendToClient(fd, msg) → envoie un message à un client
*/
#include "Parser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "NumericReplies.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cstdlib>

Parser::Parser()
{
}

Parser::~Parser()
{
}

/*
** parseClientData: Point d'entrée principal du parser
**
** Cette fonction:
** 1. Récupère le buffer du client
** 2. Le découpe par "\r\n" (séparateur IRC)
** 3. Traite chaque commande
** 4. Met à jour le buffer en supprimant les commandes traitées
*/
void Parser::parseClientData(Server* server, Client* client)
{
	std::string& buffer = client->getBuffer();

	// Chercher les séparateurs \r\n
	size_t pos = 0;
	while ((pos = buffer.find("\r\n")) != std::string::npos)
	{
		// Extraire une commande complète
		std::string line = buffer.substr(0, pos);

		// Supprimer du buffer (y compris le \r\n)
		buffer = buffer.substr(pos + 2);

		// Ignorer les lignes vides
		if (line.empty())
			continue;

		// Parser et exécuter la commande
		std::vector<std::string> parts = parseLine(line);
		if (!parts.empty())
		{
			// Si executeCommand retourne true, le client a été déconnecté (QUIT)
			// On doit sortir immédiatement pour éviter d'accéder au client supprimé
			if (executeCommand(server, client, parts))
				return;
		}
	}
}

/*
** parseLine: Découper une ligne IRC en tokens
**
** Format IRC:
**   COMMANDE arg1 arg2 :texte avec espaces
**
** Exemple:
**   "PRIVMSG #general :Bonjour tout le monde"
**   → ["PRIVMSG", "#general", "Bonjour tout le monde"]
**
** Le ":" indique que le reste de la ligne est un argument
*/
std::vector<std::string> Parser::parseLine(const std::string& line)
{
	std::vector<std::string> parts;
	std::string copy = line;

	// Supprimer les espaces inutiles en début/fin
	size_t start = copy.find_first_not_of(" \t");
	size_t end = copy.find_last_not_of(" \t");

	if (start == std::string::npos)
		return parts; // Ligne vide

	copy = copy.substr(start, end - start + 1);

	// Chercher le ":" qui marque le début d'un argument multi-mots
	size_t colonPos = copy.find(" :");
	std::string beforeColon;
	std::string afterColon;

	if (colonPos != std::string::npos)
	{
		beforeColon = copy.substr(0, colonPos);
		afterColon = copy.substr(colonPos + 2); // +2 pour " :"
	}
	else
	{
		beforeColon = copy;
		afterColon = "";
	}

	// Parser la partie avant le ":"
	std::istringstream iss(beforeColon);
	std::string token;
	while (iss >> token)
	{
		parts.push_back(token);
	}

	// Ajouter la partie après le ":" comme un seul argument
	//!afterColon.empty()
	if (colonPos != std::string::npos)
	{
		parts.push_back(afterColon);
	}

	// Convertir la commande en MAJUSCULES
	if (!parts.empty())
	{
		std::transform(parts[0].begin(), parts[0].end(), parts[0].begin(), ::toupper);
	}

	return parts;
}

/*
** executeCommand: Router vers la bonne commande en fonction du premier token
** Retourne true si le client a été déconnecté (QUIT), false sinon
*/
bool Parser::executeCommand(Server* server, Client* client,
                           const std::vector<std::string>& parts)
{
	if (parts.empty())
		return false;

	std::string cmd = parts[0];

	// Router vers la bonne fonction
	if (cmd == "PASS")
		cmd_PASS(server, client, parts);
	else if (cmd == "NICK")
		cmd_NICK(server, client, parts);
	else if (cmd == "USER")
		cmd_USER(server, client, parts);
	else if (cmd == "JOIN")
		cmd_JOIN(server, client, parts);
	else if (cmd == "PART")
		cmd_PART(server, client, parts);
	else if (cmd == "PRIVMSG")
		cmd_PRIVMSG(server, client, parts);
	else if (cmd == "QUIT")
	{
		cmd_QUIT(server, client, parts);
		return true; // Client déconnecté, ne plus accéder au client
	}
	else if (cmd == "KICK")
		cmd_KICK(server, client, parts);
	else if (cmd == "INVITE")
		cmd_INVITE(server, client, parts);
	else if (cmd == "TOPIC")
		cmd_TOPIC(server, client, parts);
	else if (cmd == "MODE")
		cmd_MODE(server, client, parts);
	else
	{
		std::string target = client->getNickname().empty() ? "*" : client->getNickname();
		server->sendToClient(client->getFd(),
			IRC::formatError(IRC::ERR_UNKNOWNCOMMAND, target, cmd + " :Unknown command"));
	}
	return false;
}
