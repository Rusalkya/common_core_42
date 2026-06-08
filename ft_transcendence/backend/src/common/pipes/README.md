# Responsable: wtohami-
# Role: Tech Lead / Backend

## Pipes de validation

Ce que tu dois faire :
- Configurer le ValidationPipe global (whitelist, forbidNonWhitelisted, transform)
- Optionnel : créer des pipes personnalisés pour des validations spécifiques
  (ex: ParseFilePipe pour la validation des uploads)

---

## 📁 Fichiers à compléter

| Fichier | Ce que tu dois faire |
|---------|---------------------|
| `validation.config.ts` | Configurer les options du ValidationPipe |
| `parse-int.pipe.ts` | Implémenter la conversion string → number |
| `trim.pipe.ts` | Implémenter le trim des strings |
| `parse-uuid.pipe.ts` | Implémenter la validation UUID |
| `index.ts` | Déjà fait ✅ |

---

## 📚 Documentation

- https://docs.nestjs.com/pipes
- https://docs.nestjs.com/techniques/validation
- https://github.com/typestack/class-validator (décorateurs de validation)
