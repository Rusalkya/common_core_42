# *Ce projet a été réalisé dans le cadre du cursus 42 par wtohami-, clfouger, rgalmich, kjolly, akrings*

# 🎨 Gribouillit - Réseau social créatif

## 📌 Description

Gribouillit est un réseau social innovant inspiré de Twitter, où les utilisateurs s’expriment à travers des dessins plutôt que du texte.

Au lieu d’écrire des tweets, les utilisateurs doivent les dessiner via un système de canvas. Cela permet une expérience plus créative, ludique et originale.

### 🚀 Fonctionnalités principales

* Publication de dessins (au lieu de texte)
* Système de dessin en temps réel
* Interactions sociales (amis, chat)
* Profils utilisateurs
* Like, commentaires et partage de dessins

---

## 👥 Équipe

### wtohami-

* Rôle : Tech Lead / Backend
* Responsabilités : architecture, API, logique serveur

### clfouger

* Rôle : Frontend
* Responsabilités : interface utilisateur, canvas de dessin, direction artistique

### rgalmich

* Rôle : Base de données & cybersécurité
* Responsabilités : schéma DB, authentification, sécurité

### kjolly

* Rôle : DevOps / Project Manager
* Responsabilités : Docker, déploiement, CI/CD, organisation

### akrings

* Rôle : Product Owner / QA
* Responsabilités : vision produit, tests, validation des features

---

## 📊 Gestion de projet

* Méthodologie Agile (Scrum)
* Réunions hebdomadaires
* Gestion des tâches avec GitHub Projects
* Communication via Discord

---

## 🛠️ Stack technique

### Frontend

* React + Vite
* TailwindCSS
* Canvas API

### Backend

* NestJS
* WebSockets (temps réel)

### Base de données

* PostgreSQL
* Prisma (ORM)

### DevOps

* Docker / Docker Compose
* Nginx
* GitHub Actions

---

## 🗄️ Schéma de base de données

Tables principales :

* users (id, email, mot de passe, avatar)
* posts (id, image, user_id)
* comments
* friends
* messages

Relations :

* Un utilisateur → plusieurs posts
* Relation plusieurs-à-plusieurs pour les amis

---

## ✨ Liste des fonctionnalités

* Authentification utilisateur (rgalmich)
* Système de dessin (clfouger)
* API backend (wtohami-)
* Chat temps réel (wtohami-)
* Infrastructure DevOps (kjolly)
* Tests et debug (akrings)

---

## 🧩 Modules

### Modules majeurs (2 pts chacun)

| Module | Statut | Responsable |
|---|---|---|
| Framework frontend + backend (NestJS + React/Vite) | ✅ Validé | wtohami- (backend), clfouger (frontend) |
| Temps réel — WebSockets (Socket.io) | ✅ Validé | wtohami- |
| Interaction utilisateur (chat, amis, profils) | ✅ Validé | wtohami- |
| API publique (REST + Swagger + clé API + rate limiting) | ✅ Validé | wtohami- |
| Gestion des utilisateurs (online status inclus) | ✅ Validé | wtohami- |
| Monitoring (Prometheus + Grafana) | ✅ Validé | kjolly |

**Sous-total majeurs : 6 × 2 = 12 pts**

### Modules mineurs (1 pt chacun)

| Module | Statut | Responsable |
|---|---|---|
| ORM — Prisma | ✅ Validé | wtohami- |
| Système de notifications (create + update + delete) | ✅ Validé | wtohami- |
| Upload de fichiers (dessins) | ✅ Validé | wtohami- |
| Chat avancé (history, typing, WebSocket) | ✅ Validé | wtohami- |
| Design system (11 composants) | ✅ Validé | clfouger |
| RGPD | +1 pt | ✅ Validé | rgalmich |

**Sous-total mineurs validés : 5 × 1 = 5 pts**

### Module personnalisé (majeur — 2 pts)

| Module | Statut | Responsable |
|---|---|---|
| Système de "tweet dessiné" (canvas → post) | ✅ Validé | clfouger + akrings |

**Sous-total custom : 2 pts**

### Justification du module personnalisé

Le **"tweet dessiné"** est un module custom majeur (2 pts) qui combine un éditeur canvas
complet (brush, eraser, line, rectangle, circle, opacity, undo/redo) avec
intégration directe dans le flux de publication. Techniquement substantiel :
- Manipulation Canvas 2D API
- Dessin de formes géométriques (lignes, rectangles, cercles)
- Pile undo/redo persistante
- Support souris + tactile
- Conversion canvas → blob → upload backend
- Affichage temps réel dans le feed via WebSocket

Il remplace concrètement la fonction "tweet" d'un réseau social classique par une
expérience créative — c'est l'identité du projet, pas un simple bonus.

---

### 🏆 Total des points

| Catégorie | Validé | Détail |
|---|---|---|
| Modules majeurs | **12 pts** | 6 × 2 |
| Modules mineurs | **5 pts** | 5 × 1 |
| Module personnalisé | **2 pts** | 1 × 2 |
| **TOTAL VALIDÉ** | **20 pts** | _(minimum requis : 14 pts)_ |


✅ **Le projet dépasse le minimum requis de 5 points (bonus 5 pts max atteint).**

---

## 🧑‍💻 Instructions

### Prérequis

* Docker
* Node.js

### Lancer le projet

```bash
git clone <repo>
cd project
docker-compose up --build
```

Accès :

* Frontend : localhost:3000
* Backend : localhost:4000

---

## 📚 Ressources

* Documentation React
* Documentation NestJS
* Documentation PostgreSQL

### Utilisation de l’IA

L’IA a été utilisée pour :

* Aide à l’architecture
* Rédaction du README
* Assistance au debug

Tout le code a été compris, vérifié et validé par l’équipe.

---

## 📈 Contributions individuelles

Chaque membre a participé à :

* Développement
* Revue de code
* Tests

### Difficultés rencontrées

* Synchronisation du dessin en temps réel
* Gestion des WebSockets

### Solutions

* Optimisation des événements
* Amélioration de la gestion du state
