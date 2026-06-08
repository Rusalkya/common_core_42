# Responsable: wtohami-
# Role: Tech Lead / Backend

## Exception Filters

Ce que tu dois faire :
- Créer un HttpExceptionFilter global pour formater toutes les réponses d'erreur
- Format uniforme : { statusCode, message, error, timestamp, path }
- Logger toutes les erreurs pour le debugging
- Ne jamais exposer les détails techniques en production (stack traces, etc.)

---

## 📚 Documentation Officielle

- **Exception Filters**: https://docs.nestjs.com/exception-filters
- **Built-in HTTP Exceptions**: https://docs.nestjs.com/exception-filters#built-in-http-exceptions
- **Custom Exceptions**: https://docs.nestjs.com/exception-filters#custom-exceptions

---

## 📁 Fichiers créés

| Fichier | Description |
|---------|-------------|
| `http-exception.filter.ts` | Filtre pour les HttpException uniquement |
| `all-exceptions.filter.ts` | Filtre global qui attrape TOUTES les erreurs |
| `index.ts` | Barrel file pour les exports |

---

## 🔧 Comment utiliser les Filters

### 1. Appliquer globalement (dans main.ts)

```typescript
import { HttpExceptionFilter } from './common/filters';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  
  // Appliquer le filter globalement
  app.useGlobalFilters(new HttpExceptionFilter());
  
  await app.listen(3000);
}
```

### 2. Appliquer via le module (avec injection de dépendances)

```typescript
// app.module.ts
import { APP_FILTER } from '@nestjs/core';
import { HttpExceptionFilter } from './common/filters';

@Module({
  providers: [
    {
      provide: APP_FILTER,
      useClass: HttpExceptionFilter,
    },
  ],
})
export class AppModule {}
```

### 3. Appliquer sur un controller ou une route

```typescript
import { UseFilters } from '@nestjs/common';
import { HttpExceptionFilter } from './common/filters';

@Controller('users')
@UseFilters(HttpExceptionFilter) // Sur tout le controller
export class UsersController {

  @Get(':id')
  @UseFilters(HttpExceptionFilter) // Ou sur une route spécifique
  findOne(@Param('id') id: string) {
    // ...
  }
}
```

---

## 🎯 Format de réponse attendu

```json
{
  "statusCode": 404,
  "message": "User not found",
  "error": "Not Found",
  "timestamp": "2024-01-15T10:30:00.000Z",
  "path": "/api/users/123"
}
```

---

## 💡 Tips

1. **Logger** : Utilise `Logger` de NestJS, pas `console.log`
2. **Production** : Vérifie `process.env.NODE_ENV` avant d'exposer des détails
3. **Validation errors** : Les erreurs de class-validator retournent un tableau de messages
4. **Ordre des filters** : Le dernier filter enregistré est exécuté en premier

---

## 🔗 Ressources supplémentaires

- [NestJS Exception Filters (YouTube)](https://www.youtube.com/results?search_query=nestjs+exception+filters)
- [Error Handling Best Practices](https://docs.nestjs.com/faq/request-lifecycle)
- [class-validator](https://github.com/typestack/class-validator) - Pour comprendre les erreurs de validation
