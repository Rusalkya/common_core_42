# ft_irc - Internet Relay Chat Server

Un serveur IRC conforme au protocole RFC 1459, écrit en C++98.

## Description

Ce projet implémente un serveur IRC capable de gérer plusieurs clients simultanément, sans fork, avec une seule boucle `poll()`. Compatible avec les clients IRC standards (irssi, WeeChat).

## Compilation

```bash
make        # Compile le projet
make clean  # Supprime les fichiers objets
make fclean # Supprime les fichiers objets et l'exécutable
make re     # Recompile entièrement
```

## Utilisation

```bash
./ircserv <port> <password>
```

**Exemple :**
```bash
./ircserv 6667 monpassword
```

## 🔌 Connexion avec un client IRC

### irssi
```bash
irssi -c 127.0.0.1 -p 6667 -w monpassword -n MonPseudo
```

### WeeChat
```
/server add irc42 127.0.0.1/6667 -password=monpassword
/connect irc42
```

### netcat (debug)
```bash
nc localhost 6667
PASS monpassword
NICK bob
USER bob 0 * :Bob Le Bricoleur
JOIN #general
PRIVMSG #general :Hello World!
```

## Commandes IRC supportées

| Commande | Description | Syntaxe |
|----------|-------------|---------|
| `PASS` | Authentification | `PASS <password>` |
| `NICK` | Définir le pseudo | `NICK <nickname>` |
| `USER` | Définir l'utilisateur | `USER <username> 0 * :<realname>` |
| `JOIN` | Rejoindre un channel | `JOIN <#channel> [key]` |
| `PART` | Quitter un channel | `PART <#channel> [reason]` |
| `PRIVMSG` | Envoyer un message | `PRIVMSG <target> :<message>` |
| `QUIT` | Quitter le serveur | `QUIT [message]` |
| `KICK` | Expulser un utilisateur | `KICK <#channel> <nick> [reason]` |
| `INVITE` | Inviter un utilisateur | `INVITE <nick> <#channel>` |
| `TOPIC` | Voir/changer le topic | `TOPIC <#channel> [new topic]` |
| `MODE` | Modifier les modes | `MODE <#channel> <+/-mode> [param]` |

## Modes de channel

| Mode | Description | Paramètre |
|------|-------------|-----------|
| `+i` | Invite-only | - |
| `+t` | Topic réservé aux ops | - |
| `+k` | Mot de passe | `<key>` |
| `+o` | Donner/retirer opérateur | `<nick>` |
| `+l` | Limite d'utilisateurs | `<limit>` |

**Exemples :**
```
MODE #general +i           # Channel invite-only
MODE #general +k secret    # Ajouter mot de passe
MODE #general +o bob       # Bob devient opérateur
MODE #general +l 10        # Limite à 10 utilisateurs
MODE #general -i           # Retirer invite-only
```

## Structure du projet

```
ircserv/
├── Makefile
├── includes/
│   ├── Server.hpp
│   ├── Client.hpp
│   ├── Channel.hpp
│   ├── Parser.hpp
│   ├── Command.hpp
│   └── NumericReplies.hpp
└── srcs/
    ├── server/
    │   ├── main.cpp
    │   └── Server.cpp
    ├── client/
    │   ├── Client.cpp
    │   └── Channel.cpp
    └── parsing/
        ├── Parser.cpp
        ├── Command.cpp
        └── commands/
            ├── Pass.cpp
            ├── Nick.cpp
            ├── User.cpp
            ├── Join.cpp
            ├── Privmsg.cpp
            ├── Kick.cpp
            ├── Invite.cpp
            ├── Topic.cpp
            ├── Mode.cpp
            └── Quit.cpp
```

## Conformité au sujet

- [x] C++98 uniquement
- [x] Pas de fork
- [x] 1 seul poll()
- [x] Sockets non-bloquants
- [x] fcntl() utilisé uniquement avec `F_SETFL, O_NONBLOCK`
- [x] Pas d'errno après recv/send
- [x] TCP/IP v4
- [x] Multi-clients simultanés
- [x] Compatible irssi/WeeChat

## 👥 Auteurs

Projet réalisé dans le cadre du cursus 42.
