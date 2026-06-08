import { ValidationPipe, ValidationPipeOptions } from '@nestjs/common';

/**
 * Configuration du ValidationPipe global
 * 
 * A UTILISER DANS main.ts:
 * app.useGlobalPipes(new ValidationPipe(validationPipeConfig));
 * 
 * DOCUMENTATION:
 * - https://docs.nestjs.com/pipes#validation-pipe
 * - https://docs.nestjs.com/techniques/validation
 */

export const validationPipeConfig: ValidationPipeOptions = {
  // Supprime les proprietes qui ne sont pas decorees dans le DTO
  // Ex: Si le DTO a { email, password } et le client envoie { email, password, isAdmin }
  // isAdmin sera automatiquement supprime
  whitelist: true,

  // Retourne une erreur 400 si le client envoie des proprietes non autorisees
  // Au lieu de les supprimer silencieusement
  forbidNonWhitelisted: true,

  // Convertit automatiquement les types selon les decorateurs
  // Ex: @Param('id') id: number → convertit "123" en 123
  transform: true,

  // Options de transformation
  transformOptions: {
    // Permet la conversion implicite des types
    enableImplicitConversion: true,
  },

  // Desactiver les messages d'erreur detailles en production (optionnel)
  // disableErrorMessages: process.env.NODE_ENV === 'production',
};

/**
 * Fonction pour creer le ValidationPipe configure
 * Utilise cette fonction dans main.ts
 */
export function createValidationPipe(): ValidationPipe {
  return new ValidationPipe(validationPipeConfig);
}
