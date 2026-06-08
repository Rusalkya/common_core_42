#!/bin/bash

# Script de test de liaison Frontend-Backend
# Vérifiez que le backend tourne sur http://localhost:3001/api

echo "🔍 Test de la connexion Frontend-Backend"
echo "========================================="
echo ""

# Test 1: Vérifier que le backend répond
echo "1️⃣  Vérification du backend..."
RESPONSE=$(curl -s -o /dev/null -w "%{http_code}" http://localhost:3001/api/health)
if [ "$RESPONSE" == "200" ] || [ "$RESPONSE" == "201" ]; then
    echo "✅ Backend OK (HTTP $RESPONSE)"
else
    echo "❌ Backend ne répond pas sur http://localhost:3001/api"
    echo "   Lancez: cd backend && npm run start:dev"
    exit 1
fi
echo ""

# Test 2: Test d'inscription (créer un user test)
echo "2️⃣  Test d'inscription..."
REGISTER=$(curl -s -X POST http://localhost:3001/api/auth/register \
  -H "Content-Type: application/json" \
  -d '{
    "email": "test@example.com",
    "username": "testuser",
    "password": "testpassword123"
  }')
echo "Réponse: $REGISTER"
echo ""

# Test 3: Test de login
echo "3️⃣  Test de connexion..."
LOGIN=$(curl -s -X POST http://localhost:3001/api/auth/login \
  -H "Content-Type: application/json" \
  -d '{
    "email": "test@example.com",
    "password": "testpassword123"
  }')
echo "Réponse: $LOGIN"
echo ""

echo "✨ Tests terminés!"
echo ""
echo "📝 Prochaines étapes:"
echo "1. Lancez le frontend: cd frontend && npm run dev"
echo "2. Ouvrez http://localhost:5173 dans votre navigateur"
echo "3. Testez la connexion avec:"
echo "   - Email: test@example.com"
echo "   - Mot de passe: testpassword123"
