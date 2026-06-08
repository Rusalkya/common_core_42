import {
  Injectable,
  NestInterceptor,
  ExecutionContext,
  CallHandler,
  Logger,
} from '@nestjs/common';
import { Observable } from 'rxjs';
import { tap } from 'rxjs/operators';
import { Request } from 'express';

/**
 * LoggingInterceptor - Log toutes les requetes avec leur duree d'execution
 * 
 * OUTPUT DANS LA CONSOLE:
 * [LoggingInterceptor] GET /api/users - 45ms
 * [LoggingInterceptor] POST /api/auth/login - 123ms
 * 
 * UTILISATION:
 * - Global: app.useGlobalInterceptors(new LoggingInterceptor())
 * - Module: { provide: APP_INTERCEPTOR, useClass: LoggingInterceptor }
 * - Controller/Route: @UseInterceptors(LoggingInterceptor)
 */

@Injectable()
export class LoggingInterceptor implements NestInterceptor {
  private readonly logger = new Logger(LoggingInterceptor.name);

  /**
   * Methode appelee pour chaque requete
   * @param context - Contexte d'execution
   * @param next - CallHandler pour continuer vers le controller
   */
  intercept(context: ExecutionContext, next: CallHandler): Observable<unknown> {
    // Recuperer les infos de la requete
    const request = context.switchToHttp().getRequest<Request>();
    const method = request.method;      // GET, POST, PUT, DELETE, etc.
    const url = request.url;            // /api/users/123
    const userAgent = request.get('user-agent') || 'unknown';

    // Enregistrer le temps de debut
    const startTime = Date.now();

    // Log avant l'execution
    this.logger.log(`Incoming: ${method} ${url}`);

    // next.handle() appelle le controller
    // tap() permet d'executer du code apres la reponse sans la modifier
    return next.handle().pipe(
      tap({
        // Appele quand la requete reussit
        next: () => {
          const duration = Date.now() - startTime;
          this.logger.log(`Completed: ${method} ${url} - ${duration}ms`);
        },
        // Appele quand la requete echoue
        error: (error) => {
          const duration = Date.now() - startTime;
          this.logger.error(`Failed: ${method} ${url} - ${duration}ms - ${error.message}`);
        },
      }),
    );
  }
}
