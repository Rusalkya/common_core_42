import {
  Injectable,
  NestInterceptor,
  ExecutionContext,
  CallHandler,
} from '@nestjs/common';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

/**
 * TransformInterceptor - Formate toutes les reponses API de maniere uniforme
 * 
 * AVANT (reponse brute):
 * { "id": 1, "name": "John" }
 * 
 * APRES (reponse formatee):
 * {
 *   "success": true,
 *   "data": { "id": 1, "name": "John" },
 *   "timestamp": "2024-01-15T10:30:00.000Z"
 * }
 * 
 * UTILISATION:
 * - Global: app.useGlobalInterceptors(new TransformInterceptor())
 * - Module: { provide: APP_INTERCEPTOR, useClass: TransformInterceptor }
 * - Controller/Route: @UseInterceptors(TransformInterceptor)
 */

// Interface pour le format de reponse uniforme
export interface ApiResponse<T> {
  success: boolean;
  data: T;
  timestamp: string;
}

@Injectable()
export class TransformInterceptor<T> implements NestInterceptor<T, ApiResponse<T>> {
  /**
   * Methode appelee pour chaque requete
   * @param context - Contexte d'execution (contient request, response, etc.)
   * @param next - CallHandler pour continuer vers le controller
   * @returns Observable avec la reponse transformee
   */
  intercept(context: ExecutionContext, next: CallHandler): Observable<ApiResponse<T>> {
    // next.handle() appelle le controller et retourne un Observable
    // pipe(map(...)) transforme la reponse avant de l'envoyer au client
    return next.handle().pipe(
      map((data) => ({
        success: true,
        data: data,
        timestamp: new Date().toISOString(),
      })),
    );
  }
}
