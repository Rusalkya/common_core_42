/**
 * Barrel file - Exporte tous les Exception Filters
 * 
 * UTILISATION:
 * import { HttpExceptionFilter, AllExceptionsFilter } from './common/filters';
 * 
 * DIFFERENCE ENTRE LES DEUX:
 * - HttpExceptionFilter: Attrape uniquement les HttpException (erreurs HTTP classiques)
 * - AllExceptionsFilter: Attrape TOUTES les erreurs (y compris les bugs inattendus)
 * 
 * RECOMMANDATION:
 * Utilise AllExceptionsFilter en global pour ne jamais laisser passer une erreur non formatee
 */

export * from './http-exception.filter';
export * from './all-exceptions.filter';
