#!/bin/bash
# ============================================
# setup-goinfre.sh - Redirige npm/node vers /goinfre
# ============================================
# Le home à 42 est limité en espace.
# Ce script déplace les caches npm/node dans /goinfre
# pour éviter les erreurs "ENOSPC: no space left on device"

USER=$(whoami)
GOINFRE="/goinfre/${USER}"

echo "🔧 Configuration npm/node vers ${GOINFRE}..."

# 1. Créer les dossiers dans goinfre
mkdir -p "${GOINFRE}/.npm"
mkdir -p "${GOINFRE}/.npm-global"
mkdir -p "${GOINFRE}/.cache"
mkdir -p "${GOINFRE}/.local/share/prisma"

# 2. Supprimer les anciens dossiers du home (libère de l'espace)
rm -rf "${HOME}/.npm"
rm -rf "${HOME}/.npm-global"
rm -rf "${HOME}/.cache/prisma"

# 3. Créer les symlinks home → goinfre
ln -sfn "${GOINFRE}/.npm" "${HOME}/.npm"
ln -sfn "${GOINFRE}/.cache" "${HOME}/.cache"

# 4. Configurer npm pour utiliser goinfre
npm config set prefix "${GOINFRE}/.npm-global"
npm config set cache "${GOINFRE}/.npm"

# 5. Variables d'environnement pour Prisma (stocke les binaires dans goinfre)
export PRISMA_ENGINES_HOME="${GOINFRE}/.local/share/prisma"
export npm_config_cache="${GOINFRE}/.npm"

# 6. Ajouter au .zshrc pour que ce soit persistant
ZSHRC="${HOME}/.zshrc"
if ! grep -q "PRISMA_ENGINES_HOME" "${ZSHRC}" 2>/dev/null; then
  echo "" >> "${ZSHRC}"
  echo "# === DrawTweet - goinfre config ===" >> "${ZSHRC}"
  echo "export PRISMA_ENGINES_HOME=\"${GOINFRE}/.local/share/prisma\"" >> "${ZSHRC}"
  echo "export npm_config_cache=\"${GOINFRE}/.npm\"" >> "${ZSHRC}"
  echo "export PATH=\"${GOINFRE}/.npm-global/bin:\$PATH\"" >> "${ZSHRC}"
  echo "# === fin goinfre config ===" >> "${ZSHRC}"
  echo "✅ Variables ajoutées à ${ZSHRC}"
fi

echo ""
echo "✅ Tout est redirigé vers ${GOINFRE}"
echo "📦 Tu peux maintenant faire : cd /goinfre/${USER}/trans/backend && npm install"
echo ""
