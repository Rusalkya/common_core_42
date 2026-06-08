# Responsable: kjolly
# Role: DevOps / Project Manager
#
# DOCKERFILE BACKEND - Image Docker du backend NestJS
#
# Ce que tu dois faire :
# - Utiliser une image Node.js LTS comme base (node:20-alpine)  |
# - Copier package.json et installer les dépendances (npm ci)  |
# - Copier le code source  |
# - Générer le client Prisma (npx prisma generate)
# - Builder le projet TypeScript (npm run build)
# - Utiliser un multi-stage build pour réduire la taille de l'image
# - Exposer le port 3000
# - Ajouter un utilisateur non-root pour la sécurité
# - Définir la commande de démarrage (node dist/main.js)
FROM node:24-alpine As builder
WORKDIR /app
COPY ./package.json ./package-lock.json ./
RUN npm ci
COPY . .
RUN npx prisma generate
RUN npm run build
# ----------------------------
# ---------- stage 2 ---------
FROM node:24-alpine As runtime
WORKDIR /app

# fix openssl pour prisma sur alpine
RUN apk add --no-cache openssl

COPY --from=builder /app/package.json ./
COPY --from=builder /app/node_modules ./node_modules
COPY --from=builder /app/dist ./dist
COPY --from=builder /app/prisma ./prisma

RUN addgroup -g 1001 nodejs && adduser -h /home/nodejs -G nodejs -u 1001 -D nodejs

# ← ajoute ça : chown AVANT de switcher user
RUN chown -R nodejs:nodejs /app

USER nodejs
EXPOSE 3001
CMD ["sh", "-c", "until node node_modules/.bin/prisma db push --accept-data-loss; do echo 'Waiting for DB...'; sleep 2; done && node dist/main.js"]