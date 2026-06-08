# Backend DrawTweet — NestJS

> Responsable : **wtohami-**
> API disponible sur `http://localhost:3001/api`
> Documentation Swagger : `http://localhost:3001/api/docs`

---

## Sommaire

1. [Pourquoi NestJS ?](#pourquoi-nestjs)
2. [Architecture](#architecture)
3. [Base de données — Prisma + PostgreSQL](#base-de-données--prisma--postgresql)
4. [Authentification JWT](#authentification-jwt)
5. [Modules API](#modules-api)
6. [Sécurité](#sécurité)
7. [WebSockets — Chat temps réel](#websockets--chat-temps-réel)
8. [Monitoring — Prometheus + Grafana](#monitoring--prometheus--grafana)
9. [Lancer le backend](#lancer-le-backend)
10. [Variables d'environnement](#variables-denvironnement)
11. [Structure des fichiers](#structure-des-fichiers)

---

## Pourquoi NestJS ?

NestJS est un framework Node.js basé sur TypeScript et inspiré d'Angular. Il impose une architecture modulaire, claire et scalable.

### Concepts clés à comprendre

| Concept | Rôle |
|---|---|
| **Module** | Unité de découpe fonctionnelle (ex: `UsersModule`, `PostsModule`) |
| **Controller** | Reçoit les requêtes HTTP et retourne les réponses |
| **Service** | Contient la logique métier (accès DB, règles, calculs) |
| **Guard** | Vérifie les permissions avant d'entrer dans un controller (ex: JWT) |
| **Interceptor** | Transforme les requêtes/réponses (ex: format uniforme, logs) |
| **Pipe** | Valide et transforme les données d'entrée (ex: type, longueur) |
| **Filter** | Intercepte les exceptions et formate les erreurs |
| **DTO** | Data Transfer Object — définit la forme attendue des données d'entrée |
| **Decorator** | Annotation TypeScript qui ajoute du comportement (`@Get()`, `@UseGuards()`, etc.) |

### Cycle d'une requête

```
Request HTTP
    └── Guard (JWT ?)
         └── Pipe (validation du body)
              └── Controller (routing)
                   └── Service (logique)
                        └── Prisma (base de données)
                             └── Response (formatée par Interceptor)
```

---

## Architecture

```
backend/src/
├── main.ts                  # Point d'entrée : configure Express, CORS, Swagger
├── app.module.ts            # Module racine : importe tout
│
├── common/                  # Utilitaires partagés
│   ├── filters/             # AllExceptionsFilter — formate toutes les erreurs
│   ├── guards/              # ThrottlerGuard global (rate limiting)
│   ├── interceptors/        # LoggingInterceptor, TransformInterceptor, SecurityLoggingInterceptor
│   ├── pipes/               # ValidationPipe (class-validator), SanitizePipe
│   └── middleware/          # (extensible)
│
├── config/                  # Configuration centralisée (app.config.ts)
│
├── prisma/                  # Service Prisma (connexion DB)
│
└── modules/
    ├── auth/                # Inscription, login, JWT
    ├── users/               # Profils utilisateurs
    ├── posts/               # Publications et likes
    ├── comments/            # Commentaires sur les posts
    ├── friends/             # Demandes d'amitié, acceptation
    ├── messages/            # Messagerie privée
    ├── notifications/       # Alertes (like, commentaire, ami)
    ├── chat/                # Gateway WebSocket Socket.io
    ├── upload/              # Upload d'images (Multer)
    ├── health/              # Health check (/api/health)
    ├── metrics/             # Endpoint Prometheus (/api/metrics)
    └── permissions/         # Système de rôles avancé
```

---

## Base de données — Prisma + PostgreSQL

### Pourquoi Prisma ?

Prisma est un ORM TypeScript qui génère un client typé à partir du schéma. Pas de SQL brut, pas de bugs de typage. Si tu changes le schéma, TypeScript te dira immédiatement où le code est cassé.

### Modèles

```
User
 ├── Post[]          (ses publications)
 ├── Comment[]       (ses commentaires)
 ├── Like[]          (ses likes, clé composite userId+postId)
 ├── Friend[]        (demandes envoyées/reçues)
 ├── Message[]       (envoyés/reçus)
 └── Notification[]  (ses alertes)

Post
 ├── User            (auteur)
 ├── Comment[]
 ├── Like[]
 └── Notification[]

Friend
 ├── status: PENDING | ACCEPTED | REJECTED
 ├── sender: User
 └── receiver: User

Message
 ├── sender: User
 ├── receiver: User
 └── read: Boolean

Notification
 └── type: LIKE | COMMENT | FRIEND_REQUEST | FRIEND_ACCEPTED | MESSAGE
```

### Commandes utiles

```bash
# Studio graphique (GUI Prisma dans le browser)
cd backend && npx prisma studio

# Créer une migration après modif du schéma
cd backend && npx prisma migrate dev --name ma_migration

# Appliquer les migrations (prod/CI)
cd backend && npx prisma migrate deploy

# Regénérer le client TypeScript
cd backend && npx prisma generate

# Accès SQL direct à la DB
docker exec -it db psql -U drawtweet -d drawtweet
```

---

## Authentification JWT

### Fonctionnement

1. L'utilisateur envoie `POST /api/auth/register` ou `POST /api/auth/login`
2. Le backend vérifie le mot de passe avec **bcrypt** (hash + sel, 10 rounds)
3. Si OK → génère un **JWT** (JSON Web Token) signé avec `JWT_SECRET`
4. Le client stocke ce token et l'envoie dans chaque requête protégée :
   ```
   Authorization: Bearer <token>
   ```
5. Le `JwtAuthGuard` vérifie et décode le token à chaque requête
6. L'identité de l'utilisateur (`req.user.id`) est disponible dans tous les controllers

### Avantage

Le serveur est **stateless** : il n'y a pas de session en mémoire. Chaque token est auto-suffisant et vérifié cryptographiquement.

### Endpoints auth

| Méthode | Route | Description |
|---|---|---|
| POST | `/api/auth/register` | Créer un compte |
| POST | `/api/auth/login` | Se connecter, recevoir un token |
| GET | `/api/auth/me` | Profil de l'utilisateur connecté (JWT requis) |

---

## Modules API

Tous les endpoints respectent le format de réponse uniforme géré par `TransformInterceptor` :

```json
{
  "success": true,
  "data": { ... },
  "timestamp": "2026-05-11T12:00:00.000Z"
}
```

En cas d'erreur :
```json
{
  "statusCode": 404,
  "message": "User #999 not found",
  "timestamp": "...",
  "path": "/api/users/999"
}
```

### Users — `/api/users`

| Méthode | Route | Auth | Description |
|---|---|---|---|
| GET | `/api/users` | Non | Liste tous les utilisateurs |
| GET | `/api/users/:id` | Non | Profil d'un utilisateur |
| PATCH | `/api/users/:id` | JWT | Modifier son profil |
| DELETE | `/api/users/:id` | JWT | Supprimer son compte |
| GET | `/api/users/search?q=...` | Non | Rechercher un utilisateur |

### Posts — `/api/posts`

| Méthode | Route | Auth | Description |
|---|---|---|---|
| GET | `/api/posts` | Non | Fil d'actualité (tous les posts) |
| POST | `/api/posts` | JWT | Créer un post (imageUrl + caption) |
| GET | `/api/posts/:id` | Non | Détail d'un post (avec likes et commentaires) |
| PATCH | `/api/posts/:id` | JWT | Modifier sa légende |
| DELETE | `/api/posts/:id` | JWT | Supprimer son post |
| POST | `/api/posts/:id/like` | JWT | Liker un post |
| DELETE | `/api/posts/:id/like` | JWT | Unliker un post |
| GET | `/api/posts/user/:id` | Non | Posts d'un utilisateur |

### Comments — `/api/comments`

| Méthode | Route | Auth | Description |
|---|---|---|---|
| POST | `/api/comments` | JWT | Ajouter un commentaire (`postId` + `content`) |
| GET | `/api/comments/post/:id` | Non | Commentaires d'un post |
| PATCH | `/api/comments/:id` | JWT | Modifier son commentaire |
| DELETE | `/api/comments/:id` | JWT | Supprimer son commentaire |

### Friends — `/api/friends`

| Méthode | Route | Auth | Description |
|---|---|---|---|
| POST | `/api/friends/request/:userId` | JWT | Envoyer une demande d'ami |
| GET | `/api/friends/pending` | JWT | Demandes en attente reçues |
| PATCH | `/api/friends/:id/accept` | JWT | Accepter une demande |
| PATCH | `/api/friends/:id/reject` | JWT | Refuser une demande |
| GET | `/api/friends` | JWT | Liste des amis |
| DELETE | `/api/friends/:id` | JWT | Supprimer une relation |

### Messages — `/api/messages`

| Méthode | Route | Auth | Description |
|---|---|---|---|
| POST | `/api/messages` | JWT | Envoyer un message (`receiverId` + `content`) |
| GET | `/api/messages` | JWT | Toutes les conversations |
| GET | `/api/messages/:userId` | JWT | Conversation avec un utilisateur |
| GET | `/api/messages/unread` | JWT | Nombre de messages non lus |
| PATCH | `/api/messages/:id/read` | JWT | Marquer un message comme lu |

### Notifications — `/api/notifications`

| Méthode | Route | Auth | Description |
|---|---|---|---|
| GET | `/api/notifications` | JWT | Mes notifications |
| GET | `/api/notifications/unread` | JWT | Nombre de non lues |
| PATCH | `/api/notifications/read-all` | JWT | Tout marquer comme lu |

### Health — `/api/health`

```json
GET /api/health
{
  "success": true,
  "data": {
    "status": "ok",
    "timestamp": "...",
    "uptime": 1234.5
  }
}
```

---

## Sécurité

### Ce qui est en place

| Mécanisme | Librairie | Rôle |
|---|---|---|
| **Hash des mots de passe** | bcrypt (10 rounds) | Les mots de passe ne sont jamais stockés en clair |
| **JWT** | @nestjs/jwt + passport-jwt | Authentification stateless et vérifiable |
| **Rate limiting** | @nestjs/throttler | 100 req/min globalement, 5 logins/min en prod |
| **Validation des entrées** | class-validator + ValidationPipe | Rejette tout body malformé (400 Bad Request) |
| **Sanitization** | SanitizePipe custom | Trim des strings, suppression des `<>` (XSS basique) |
| **Headers HTTP** | helmet | CSP, HSTS, X-Frame-Options, etc. |
| **CORS strict** | NestJS cors | Whitelist d'origines via `CORS_ORIGIN` env var |
| **Logs de sécurité** | SecurityLoggingInterceptor | Log toutes les erreurs 4xx/5xx avec IP et User-Agent |

### Rate limiting en détail

- **Global** : 100 requêtes / minute par IP
- **Auth** : 5 tentatives de login / minute en production (1000 en dev)
- Configuré dans `app.module.ts` via `ThrottlerModule.forRoot()`
- Le throttle `auth` est appliqué spécifiquement sur `POST /auth/register` et `POST /auth/login`

### Validation des DTOs

Chaque body de requête est validé via des classes annotées :

```typescript
// Exemple : CreateUserDto
class CreateUserDto {
  @IsEmail()
  @MaxLength(255)
  email: string;

  @IsString()
  @MinLength(8)
  @MaxLength(100)
  password: string;

  @IsString()
  @MinLength(3)
  @MaxLength(20)
  username: string;
}
```

Si un champ est manquant ou mal typé → réponse `400 Bad Request` automatique.

---

## WebSockets — Chat temps réel

Le module `chat` expose un **Gateway Socket.io** sur le même port que l'API REST (3001).

### Connexion

```javascript
// Côté frontend
import { io } from 'socket.io-client';
const socket = io('http://localhost:3001', {
  auth: { token: 'eyJhbGci...' }  // JWT dans les headers de connexion
});
```

### Événements disponibles

| Événement (client → serveur) | Description |
|---|---|
| `authenticate` | Authentifier la connexion WebSocket avec le JWT |
| `joinRoom` | Rejoindre une room de chat (`roomId`) |
| `leaveRoom` | Quitter une room |
| `sendMessage` | Envoyer un message dans une room |
| `typing` | Indiquer que l'utilisateur est en train de taper |

### Sécurité

Le Gateway vérifie le JWT à la connexion. Une connexion sans token valide est rejetée.

---

## Monitoring — Prometheus + Grafana

### Architecture

```
Backend (:3001/api/metrics)
    └── Prometheus (:9090)  — scrape les métriques toutes les 15s
         └── Grafana (:3003)  — dashboards de visualisation
```

### Accès

- Prometheus : `http://localhost:9090`
- Grafana : `http://localhost:3003` (admin / admin)

### Métriques exposées

L'endpoint `/api/metrics` expose des métriques au format Prometheus (compteurs, histogrammes, gauges) sur :
- Nombre de requêtes HTTP par route et status code
- Temps de réponse
- Connexions WebSocket actives
- Uptime du serveur

---

## Lancer le backend

### Via Makefile (recommandé)

```bash
# Lancer tout (DB + backend + frontend)
make up

# Relancer de zéro
make re

# Arrêter tous les services
make down

# Voir les logs backend en temps réel
make logs-back

# Accès au shell SQL de la DB
make db
```

### En direct (développement)

```bash
cd backend

# Installer les dépendances
npm install

# Générer le client Prisma
npx prisma generate

# Appliquer les migrations
npx prisma migrate deploy

# Lancer en mode watch (rechargement automatique)
npm run start:dev
```

### Tester l'API

```bash
# Script de test automatisé (40 tests)
bash test-api.sh

# Ou via Swagger
open http://localhost:3001/api/docs
```

---

## Variables d'environnement

Le fichier `.env` à la racine de `backend/` :

```env
# Base de données
DATABASE_URL="postgresql://drawtweet:drawtweet@localhost:5432/drawtweet"

# JWT
JWT_SECRET="ton_secret_tres_long_et_aleatoire"
JWT_EXPIRATION="7d"

# Sécurité
BCRYPT_ROUNDS=10

# CORS (origines autorisées, séparées par des virgules)
CORS_ORIGIN="http://localhost:3000,http://localhost:5173"

# Environnement
NODE_ENV="development"
```

> En production, `NODE_ENV=production` active les limites throttle strictes (5 logins/min).

---

## Structure des fichiers

Chaque module suit la même structure :

```
modules/users/
├── users.module.ts        # Déclare le module, importe les dépendances
├── users.controller.ts    # Définit les routes HTTP (@Get, @Post, etc.)
├── user.service.ts        # Logique métier, appels Prisma
└── dto/
    ├── create-user.dto.ts # Validation du body de création
    └── update-user.dto.ts # Validation du body de modification
```

### Comment ajouter un nouveau module

```bash
# Générer avec le CLI NestJS
cd backend
npx @nestjs/cli generate module modules/mon-module
npx @nestjs/cli generate controller modules/mon-module
npx @nestjs/cli generate service modules/mon-module
```

Puis importer le module dans `app.module.ts`.

---

## Ressources

- [Documentation NestJS](https://docs.nestjs.com)
- [Documentation Prisma](https://www.prisma.io/docs)
- [Documentation JWT](https://jwt.io)
- [Documentation Socket.io](https://socket.io/docs/v4)
- [Documentation Swagger/OpenAPI](https://swagger.io/docs)
- Swagger interactif du projet : `http://localhost:3001/api/docs`
