#!/bin/bash
# ============================================
# test-api.sh - Tests complets de l'API DrawTweet
# ============================================

BASE="http://localhost:3001/api"
TOKEN=""
TOKEN2=""

green() { echo -e "\033[32m✅ $1\033[0m"; }
red() { echo -e "\033[31m❌ $1\033[0m"; }
title() { echo -e "\n\033[1;36m========== $1 ==========\033[0m"; }

# ============================================
title "1. HEALTH CHECK"
# ============================================
echo "GET /api/health"
curl -s $BASE/health | python3 -m json.tool

# ============================================
title "2. AUTH - REGISTER (user1)"
# ============================================
echo "POST /api/auth/register"
RES=$(curl -s -X POST $BASE/auth/register \
  -H "Content-Type: application/json" \
  -d '{"email":"user1@test.com","password":"password123","username":"user1"}')
echo $RES | python3 -m json.tool
TOKEN=$(echo $RES | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('access_token',''))" 2>/dev/null)
# Si register a echoue (user existe deja), on se connecte
if [ -z "$TOKEN" ]; then
  RES=$(curl -s -X POST $BASE/auth/login \
    -H "Content-Type: application/json" \
    -d '{"email":"user1@test.com","password":"password123"}')
  TOKEN=$(echo $RES | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('access_token',''))" 2>/dev/null)
  echo "(user1 existait deja, login effectue)"
fi
USER1_ID=$(echo $RES | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('user',{}).get('id',1))" 2>/dev/null)
echo "TOKEN1: ${TOKEN:0:30}..."

# ============================================
title "3. AUTH - REGISTER (user2)"
# ============================================
echo "POST /api/auth/register"
RES2=$(curl -s -X POST $BASE/auth/register \
  -H "Content-Type: application/json" \
  -d '{"email":"user2@test.com","password":"password123","username":"user2"}')
echo $RES2 | python3 -m json.tool
TOKEN2=$(echo $RES2 | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('access_token',''))" 2>/dev/null)
# Si register a echoue (user existe deja), on se connecte
if [ -z "$TOKEN2" ]; then
  RES2=$(curl -s -X POST $BASE/auth/login \
    -H "Content-Type: application/json" \
    -d '{"email":"user2@test.com","password":"password123"}')
  TOKEN2=$(echo $RES2 | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('access_token',''))" 2>/dev/null)
  echo "(user2 existait deja, login effectue)"
fi
USER2_ID=$(echo $RES2 | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('user',{}).get('id',2))" 2>/dev/null)
echo "TOKEN2: ${TOKEN2:0:30}..."

# ============================================
title "4. AUTH - REGISTER DUPLICATE (doit échouer)"
# ============================================
echo "POST /api/auth/register (même email)"
curl -s -X POST $BASE/auth/register \
  -H "Content-Type: application/json" \
  -d '{"email":"user1@test.com","password":"password123","username":"user1bis"}' | python3 -m json.tool

# ============================================
title "5. AUTH - LOGIN"
# ============================================
echo "POST /api/auth/login"
curl -s -X POST $BASE/auth/login \
  -H "Content-Type: application/json" \
  -d '{"email":"user1@test.com","password":"password123"}' | python3 -m json.tool

# ============================================
title "6. AUTH - LOGIN MAUVAIS MDP (doit échouer)"
# ============================================
echo "POST /api/auth/login (wrong password)"
curl -s -X POST $BASE/auth/login \
  -H "Content-Type: application/json" \
  -d '{"email":"user1@test.com","password":"wrongpass123"}' | python3 -m json.tool

# ============================================
title "7. AUTH - GET ME (avec token)"
# ============================================
echo "GET /api/auth/me"
curl -s $BASE/auth/me \
  -H "Authorization: Bearer $TOKEN" | python3 -m json.tool

# ============================================
title "8. AUTH - GET ME (sans token - doit échouer)"
# ============================================
echo "GET /api/auth/me (no token)"
curl -s $BASE/auth/me | python3 -m json.tool

# ============================================
title "9. USERS - GET ALL"
# ============================================
echo "GET /api/users"
curl -s $BASE/users | python3 -m json.tool

# ============================================
title "10. USERS - GET BY ID"
# ============================================
echo "GET /api/users/$USER1_ID"
curl -s $BASE/users/$USER1_ID | python3 -m json.tool

# ============================================
title "11. USERS - UPDATE"
# ============================================
echo "PATCH /api/users/$USER1_ID"
curl -s -X PATCH $BASE/users/$USER1_ID \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN" \
  -d '{"bio":"Je suis un artiste DrawTweet!"}' | python3 -m json.tool

# ============================================
title "12. USERS - GET NOT FOUND (doit échouer)"
# ============================================
echo "GET /api/users/9999"
curl -s $BASE/users/9999 | python3 -m json.tool

# ============================================
title "13. POSTS - CREATE"
# ============================================
echo "POST /api/posts"
RES_POST=$(curl -s -X POST $BASE/posts \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN" \
  -d '{"imageUrl":"https://example.com/drawing1.png","content":"Mon premier dessin!"}')
echo $RES_POST | python3 -m json.tool
POST1_ID=$(echo $RES_POST | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('id',''))" 2>/dev/null)

# ============================================
title "14. POSTS - CREATE (user2)"
# ============================================
echo "POST /api/posts (user2)"
RES_POST2=$(curl -s -X POST $BASE/posts \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN2" \
  -d '{"imageUrl":"https://example.com/drawing2.png","content":"Dessin de user2"}')
echo $RES_POST2 | python3 -m json.tool
POST2_ID=$(echo $RES_POST2 | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('id',''))" 2>/dev/null)

# ============================================
title "15. POSTS - GET ALL"
# ============================================
echo "GET /api/posts"
curl -s $BASE/posts | python3 -m json.tool

# ============================================
title "16. POSTS - GET BY ID"
# ============================================
echo "GET /api/posts/$POST1_ID"
curl -s $BASE/posts/$POST1_ID | python3 -m json.tool

# ============================================
title "17. POSTS - UPDATE"
# ============================================
echo "PATCH /api/posts/$POST1_ID"
curl -s -X PATCH $BASE/posts/$POST1_ID \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN" \
  -d '{"caption":"Caption modifiee!"}' | python3 -m json.tool

# ============================================
title "18. POSTS - LIKE"
# ============================================
echo "POST /api/posts/$POST1_ID/like"
curl -s -X POST $BASE/posts/$POST1_ID/like \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN2" | python3 -m json.tool

# ============================================
title "19. POSTS - GET (verifier le like)"
# ============================================
echo "GET /api/posts/$POST1_ID"
curl -s $BASE/posts/$POST1_ID | python3 -m json.tool

# ============================================
title "20. POSTS - UNLIKE"
# ============================================
echo "DELETE /api/posts/$POST1_ID/like"
curl -s -X DELETE $BASE/posts/$POST1_ID/like \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN2" | python3 -m json.tool

# ============================================
title "21. POSTS - GET BY USER"
# ============================================
echo "GET /api/posts/user/$USER1_ID"
curl -s $BASE/posts/user/$USER1_ID | python3 -m json.tool

# ============================================
title "22. COMMENTS - CREATE"
# ============================================
echo "POST /api/comments"
RES_COMMENT=$(curl -s -X POST $BASE/comments \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN2" \
  -d "{\"postId\":$POST1_ID,\"content\":\"Super dessin!\"}")
echo $RES_COMMENT | python3 -m json.tool
COMMENT1_ID=$(echo $RES_COMMENT | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('id',''))" 2>/dev/null)

# ============================================
title "23. COMMENTS - GET BY POST"
# ============================================
echo "GET /api/comments/post/$POST1_ID"
curl -s $BASE/comments/post/$POST1_ID | python3 -m json.tool

# ============================================
title "24. COMMENTS - UPDATE"
# ============================================
echo "PATCH /api/comments/$COMMENT1_ID"
curl -s -X PATCH $BASE/comments/$COMMENT1_ID \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN2" \
  -d '{"content":"Commentaire modifie!"}' | python3 -m json.tool

# ============================================
title "25. FRIENDS - SEND REQUEST"
# ============================================
echo "POST /api/friends/request/$USER2_ID (user1 -> user2)"
RES_FRIEND=$(curl -s -X POST $BASE/friends/request/$USER2_ID \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN")
echo $RES_FRIEND | python3 -m json.tool
FRIEND_ID=$(echo $RES_FRIEND | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('id',''))" 2>/dev/null)

# ============================================
title "26. FRIENDS - GET PENDING"
# ============================================
echo "GET /api/friends/pending (user2)"
curl -s $BASE/friends/pending \
  -H "Authorization: Bearer $TOKEN2" | python3 -m json.tool

# ============================================
title "27. FRIENDS - ACCEPT"
# ============================================
echo "PATCH /api/friends/$FRIEND_ID/accept (user2 accepte)"
curl -s -X PATCH $BASE/friends/$FRIEND_ID/accept \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN2" | python3 -m json.tool

# ============================================
title "28. FRIENDS - GET FRIENDS"
# ============================================
echo "GET /api/friends (user1)"
curl -s $BASE/friends \
  -H "Authorization: Bearer $TOKEN" | python3 -m json.tool

# ============================================
title "29. MESSAGES - SEND"
# ============================================
echo "POST /api/messages (user1 -> user2)"
RES_MSG=$(curl -s -X POST $BASE/messages \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN" \
  -d "{\"receiverId\":$USER2_ID,\"content\":\"Salut! Tu dessines bien!\"}")
echo $RES_MSG | python3 -m json.tool
MSG1_ID=$(echo $RES_MSG | python3 -c "import sys,json; d=json.load(sys.stdin); print(d.get('data',d).get('id',''))" 2>/dev/null)

# ============================================
title "30. MESSAGES - SEND (reply)"
# ============================================
echo "POST /api/messages (user2 -> user1)"
curl -s -X POST $BASE/messages \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer $TOKEN2" \
  -d "{\"receiverId\":$USER1_ID,\"content\":\"Merci beaucoup!\"}" | python3 -m json.tool

# ============================================
title "31. MESSAGES - GET CONVERSATION"
# ============================================
echo "GET /api/messages/$USER2_ID (conversation user1<->user2)"
curl -s $BASE/messages/$USER2_ID \
  -H "Authorization: Bearer $TOKEN" | python3 -m json.tool

# ============================================
title "32. MESSAGES - GET ALL CONVERSATIONS"
# ============================================
echo "GET /api/messages"
curl -s $BASE/messages \
  -H "Authorization: Bearer $TOKEN" | python3 -m json.tool

# ============================================
title "33. MESSAGES - UNREAD COUNT"
# ============================================
echo "GET /api/messages/unread"
curl -s $BASE/messages/unread \
  -H "Authorization: Bearer $TOKEN" | python3 -m json.tool

# ============================================
title "34. MESSAGES - MARK AS READ"
# ============================================
echo "PATCH /api/messages/$MSG1_ID/read"
curl -s -X PATCH $BASE/messages/$MSG1_ID/read \
  -H "Authorization: Bearer $TOKEN2" | python3 -m json.tool

# ============================================
title "35. NOTIFICATIONS - GET"
# ============================================
echo "GET /api/notifications"
curl -s $BASE/notifications \
  -H "Authorization: Bearer $TOKEN" | python3 -m json.tool

# ============================================
title "36. NOTIFICATIONS - UNREAD COUNT"
# ============================================
echo "GET /api/notifications/unread"
curl -s $BASE/notifications/unread \
  -H "Authorization: Bearer $TOKEN" | python3 -m json.tool

# ============================================
title "37. NOTIFICATIONS - MARK ALL READ"
# ============================================
echo "PATCH /api/notifications/read-all"
curl -s -X PATCH $BASE/notifications/read-all \
  -H "Authorization: Bearer $TOKEN" | python3 -m json.tool

# ============================================
title "38. COMMENTS - DELETE"
# ============================================
echo "DELETE /api/comments/$COMMENT1_ID"
curl -s -X DELETE $BASE/comments/$COMMENT1_ID \
  -H "Authorization: Bearer $TOKEN2" | python3 -m json.tool

# ============================================
title "39. POSTS - DELETE"
# ============================================
echo "DELETE /api/posts/$POST2_ID"
curl -s -X DELETE $BASE/posts/$POST2_ID \
  -H "Authorization: Bearer $TOKEN2" | python3 -m json.tool

# ============================================
title "40. FRIENDS - DELETE"
# ============================================
echo "DELETE /api/friends/$FRIEND_ID"
curl -s -X DELETE $BASE/friends/$FRIEND_ID \
  -H "Authorization: Bearer $TOKEN" | python3 -m json.tool

echo ""
echo "============================================"
echo "🏁 TESTS TERMINÉS"
echo "============================================"
