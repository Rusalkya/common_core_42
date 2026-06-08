# Responsable: wtohami- + rgalmich
# Role: Tech Lead + Sécurité

## Configuration

Ce que vous devez faire :
- wtohami- : Créer la configuration de l'application (port, cors, etc.) ✅ FAIT
- rgalmich : Créer la configuration JWT (secret, expiration, algorithme)
- rgalmich : Créer la configuration de la base de données (URL, pool, SSL)
- Utiliser @nestjs/config avec validation Joi des variables d'environnement
- Ne JAMAIS hardcoder de secrets dans le code

---

## 📁 Fichiers

| Fichier | Responsable | Status |
|---------|-------------|--------|
| `app.config.ts` | wtohami- | ✅ Fait |
| `jwt.config.ts` | rgalmich | ❌ À faire |
| `database.config.ts` | rgalmich | ❌ À faire |
| `index.ts` | wtohami- | ✅ Fait |

---

## 🔧 Utilisation

```typescript
// Dans un service ou controller
constructor(private configService: ConfigService) {}

// Accéder aux valeurs
const port = this.configService.get<number>('app.port');
const frontendUrl = this.configService.get<string>('app.frontendUrl');
```
