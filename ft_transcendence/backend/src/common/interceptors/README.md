# Responsable: wtohami-
# Role: Tech Lead / Backend

## Interceptors

Ce que tu dois faire :
- Créer un TransformInterceptor pour formater les réponses API de manière uniforme
- Créer un LoggingInterceptor pour logger les requêtes (méthode, URL, durée)
- Optionnel : CacheInterceptor pour le caching des requêtes fréquentes

---

## 📁 Fichiers créés

| Fichier | Description |
|---------|-------------|
| `transform.interceptor.ts` | Formate toutes les réponses API uniformément |
| `logging.interceptor.ts` | Log les requêtes avec leur durée |
| `timeout.interceptor.ts` | Limite le temps d'exécution des requêtes |
| `index.ts` | Barrel file pour les exports |

---

## 🔄 Qu'est-ce qu'un Interceptor ?

```
Client → Request → INTERCEPTOR (avant) → Controller → INTERCEPTOR (après) → Response → Client
```

Un interceptor peut :
- **Transformer** la réponse avant de l'envoyer
- **Logger** les requêtes
- **Ajouter un timeout**
- **Gérer le cache**

---

## 📝 Exemple de transformation

**AVANT (réponse brute du controller):**
```json
{ "id": 1, "name": "John" }
```

**APRÈS (avec TransformInterceptor):**
```json
{
  "success": true,
  "data": { "id": 1, "name": "John" },
  "timestamp": "2024-01-15T10:30:00.000Z"
}
```

---

## 🔧 Comment utiliser

### Global (dans main.ts)
```typescript
import { TransformInterceptor, LoggingInterceptor } from './common/interceptors';

app.useGlobalInterceptors(
  new LoggingInterceptor(),
  new TransformInterceptor(),
);
```

### Via le module (avec injection de dépendances)
```typescript
import { APP_INTERCEPTOR } from '@nestjs/core';
import { TransformInterceptor } from './common/interceptors';

@Module({
  providers: [
    {
      provide: APP_INTERCEPTOR,
      useClass: TransformInterceptor,
    },
  ],
})
export class AppModule {}
```

### Sur un controller ou une route
```typescript
import { UseInterceptors } from '@nestjs/common';
import { LoggingInterceptor } from './common/interceptors';

@Controller('users')
@UseInterceptors(LoggingInterceptor)
export class UsersController {}
```

---

## 📚 Documentation

- https://docs.nestjs.com/interceptors
- https://rxjs.dev/guide/operators (pour comprendre pipe, map, tap)
