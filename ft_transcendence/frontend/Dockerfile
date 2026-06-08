# Responsable: kjolly
# Role: DevOps / Project Manager
#
# DOCKERFILE FRONTEND - Image Docker du frontend React
#
# Ce que tu dois faire :
# - Utiliser node:20-alpine pour le build
# - Copier package.json et installer les dépendances
# - Copier le code source et builder (npm run build)
# - Multi-stage : utiliser nginx:alpine pour servir les fichiers statiques
# - Copier le build dans /usr/share/nginx/html
# - Configurer nginx pour le SPA (fallback sur index.html)
# - Exposer le port 80

# ---------- stage 1 ---------
FROM node:24-alpine As builder
#? node:24 car version LTS ("long term support") donc stable et recent

WORKDIR /app

COPY ./package.json ./package-lock.json ./

RUN npm ci

COPY . .

RUN npm run build
# ----------------------------
# ---------- stage 2 ---------
FROM nginx:1.30.0-alpine As waiter

WORKDIR /app

COPY --from=builder /app/dist /usr/share/nginx/html

COPY ./nginx.conf /etc/nginx/conf.d/default.conf

EXPOSE 80

CMD [ "nginx", "-g", "daemon off;" ]