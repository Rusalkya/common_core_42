# Responsable: akrings
# Role: Product Owner / QA

## Tests

Ce que tu dois faire :
- Écrire les tests end-to-end (e2e) de l'API avec supertest
- Tester tous les endpoints principaux :
  - Auth : inscription, connexion, déconnexion
  - Posts : création de dessin, récupération du feed, like, suppression
  - Comments : ajout, récupération, suppression
  - Friends : demande, acceptation, liste
  - Users : profil, mise à jour, recherche
  - Messages : envoi, historique
- Tester les cas d'erreur (401 non authentifié, 403 non autorisé, 404 not found)
- Tester les validations des DTOs (données invalides)
- Préparer un fichier jest.config pour les tests e2e
- Travailler avec rgalmich pour les tests de sécurité
