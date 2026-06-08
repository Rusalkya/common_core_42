import {
  Injectable,
  NestInterceptor,
  ExecutionContext,
  CallHandler,
  RequestTimeoutException,
} from '@nestjs/common';
import { Observable, throwError, TimeoutError } from 'rxjs';
import { catchError, timeout } from 'rxjs/operators';

/**
 * TimeoutInterceptor - Limite le temps d'execution des requetes
 * 
 * Si une requete prend plus de X secondes, elle est automatiquement annulee
 * et retourne une erreur 408 Request Timeout.
 * 
 * UTILISATION:
 * - Global: app.useGlobalInterceptors(new TimeoutInterceptor())
 * - Controller/Route: @UseInterceptors(TimeoutInterceptor)
 * 
 * PERSONNALISATION:
 * Tu peux changer la valeur du timeout (par defaut 30 secondes)
 */

@Injectable()
export class TimeoutInterceptor implements NestInterceptor {
  // Timeout en millisecondes (30 secondes par defaut)
  private readonly timeoutMs: number;

  constructor(timeoutMs: number = 30000) {
    this.timeoutMs = timeoutMs;
  }

  intercept(context: ExecutionContext, next: CallHandler): Observable<unknown> {
    return next.handle().pipe(
      // Definir le timeout
      timeout(this.timeoutMs),
      // Gerer l'erreur de timeout
      catchError((err) => {
        if (err instanceof TimeoutError) {
          return throwError(() => new RequestTimeoutException('Request timeout'));
        }
        return throwError(() => err);
      }),
    );
  }
}
