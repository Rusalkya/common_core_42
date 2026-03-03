#ifndef NUMERIC_REPLIES_HPP
#define NUMERIC_REPLIES_HPP

#include <string>

/*
 RÉPONSES NUMÉRIQUES IRC
 Format: :<serveur> <code> <client> :message\r\n
 Exemples de codes d'erreur et réponses
*/

namespace IRC
{
	// succes
	const std::string RPL_WELCOME          = "001";
	const std::string RPL_YOURHOST         = "002";
	const std::string RPL_CREATED          = "003";
	const std::string RPL_MYINFO           = "004";
	const std::string RPL_UMODEIS          = "221";

	const std::string RPL_CHANNELMODEIS    = "324";
	const std::string RPL_NOTOPIC          = "331";
	const std::string RPL_TOPIC            = "332";
	const std::string RPL_INVITING         = "341";
	const std::string RPL_NAMREPLY         = "353";
	const std::string RPL_ENDOFNAMES       = "366";

	// erreur
	const std::string ERR_PASSWDMISMATCH   = "464"; // Mot de passe incorrect
	const std::string ERR_NONICKNAMEGIVEN  = "431"; // Pas de nick fourni
	const std::string ERR_ERRONEUSNICKNAME = "432"; // Nick invalide
	const std::string ERR_NICKNAMEINUSE    = "433"; // Nick déjà pris
	const std::string ERR_NOTREGISTERED    = "451"; // Client non enregistré
	const std::string ERR_NEEDMOREPARAMS   = "461"; // Pas assez de paramètres
	const std::string ERR_UNKNOWNCOMMAND   = "421"; // Commande inconnue
	const std::string ERR_ALREADYREGISTRED = "462"; // Déjà enregistré
	const std::string ERR_NOPRIVILEGES     = "481"; // Pas les permissions
	const std::string ERR_CHANOPRIVSNEEDED = "482"; // Pas OP sur le channel

	// erreur channel
	const std::string ERR_NOSUCHCHANNEL    = "403"; // Channel inexistant
	const std::string ERR_NOTONCHANNEL     = "442"; // Pas sur ce channel
	const std::string ERR_USERONCHANNEL    = "443"; // User déjà sur le channel
	const std::string ERR_USERNOTINCHANNEL = "441"; // User pas dans le channel
	const std::string ERR_TOOMANYCHANNELS  = "405"; // Trop de channels
	const std::string ERR_INVITEONLYCHAN   = "473"; // Channel en invite only
	const std::string ERR_BADCHANNELKEY    = "475"; // Mauvais mot de passe
	const std::string ERR_CHANNELISFULL    = "471"; // Channel plein

	// erreur user
	const std::string ERR_NOSUCHNICK       = "401"; // Nick inexistant
	const std::string ERR_NORECIPIENT      = "411"; // Pas de destinataire
	const std::string ERR_NOTEXTTOSEND     = "412"; // Pas de texte


	// Fonction helper pour formater une réponse
	inline std::string formatReply(const std::string& code, const std::string& nick, const std::string& message)
	{
		return ":" + std::string("localhost") + " " + code + " " + nick + " " + message + "\r\n";
	}
	inline std::string formatError(const std::string& code, const std::string& nick, const std::string& message)
	{
		return formatReply(code, nick, message);
	}
}

#endif
