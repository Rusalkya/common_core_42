# Responsable: rgalmich
# Role: Base de données & Cybersécurité

## Guards globaux

Ce que tu dois faire :
- Créer un JwtAuthGuard global qui protège toutes les routes par défaut
- Créer un ThrottlerGuard pour le rate limiting (protection brute force)
- Les guards spécifiques aux modules sont dans modules/permissions/guards/
