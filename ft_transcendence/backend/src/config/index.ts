/**
 * ============================================
 * CONFIG INDEX - Exporte toutes les configs
 * ============================================
 * 
 * UTILISATION dans app.module.ts:
 * 
 * import { appConfig } from './config';
 * 
 * @Module({
 *   imports: [
 *     ConfigModule.forRoot({
 *       load: [appConfig],
 *       isGlobal: true,
 *     }),
 *   ],
 * })
 * 
 * Responsable: wtohami- (Tech Lead)
 */

export { default as appConfig } from './app.config';

// Les configs suivantes seront ajoutees par rgalmich :
// export { default as jwtConfig } from './jwt.config';
// export { default as databaseConfig } from './database.config';
