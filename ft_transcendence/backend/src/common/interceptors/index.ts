/**
 * Barrel file - Exporte tous les Interceptors
 * 
 * UTILISATION:
 * import { TransformInterceptor, LoggingInterceptor } from './common/interceptors';
 * 
 * QU'EST-CE QU'UN INTERCEPTOR ?
 * Un interceptor peut:
 * - Transformer la reponse avant de l'envoyer (TransformInterceptor)
 * - Logger les requetes (LoggingInterceptor)
 * - Ajouter un timeout (TimeoutInterceptor)
 * - Gerer le cache
 * - Et bien plus...
 * 
 * ORDRE D'EXECUTION:
 * Request → Interceptor (avant) → Controller → Interceptor (apres) → Response
 */

export * from './transform.interceptor';
export * from './logging.interceptor';
export * from './timeout.interceptor';
