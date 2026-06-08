import { registerAs } from '@nestjs/config';

/**
 * ============================================
 * APP CONFIG - Configuration de l'application
 * ============================================
 * 
 * Centralise la configuration generale de l'app :
 * - Port du serveur
 * - URL du frontend (CORS)
 * - Prefixe API
 * - Environnement (dev/prod)
 * 
 * UTILISATION:
 * const port = this.configService.get<number>('app.port');
 * const frontendUrl = this.configService.get<string>('app.frontendUrl');
 * 
 * Responsable: wtohami- (Tech Lead)
 */

export default registerAs('app', () => ({
  // Environnement (development, production, test)
  env: process.env.NODE_ENV || 'development',

  // Port du serveur backend
  port: parseInt(process.env.PORT, 10) || 3001,

  // URL du frontend pour CORS
  frontendUrl: process.env.FRONTEND_URL || 'http://localhost:3000',

  // Prefixe global des routes API
  apiPrefix: process.env.API_PREFIX || 'api',

  // Nom de l'application (pour Swagger, logs, etc.)
  name: process.env.APP_NAME || 'Trans API',

  // Version de l'API
  version: process.env.API_VERSION || '1.0',
}));
