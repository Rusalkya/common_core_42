import {
  ExceptionFilter,
  Catch,
  ArgumentsHost,
  HttpException,
  HttpStatus,
  Logger,
} from '@nestjs/common';
import { Request, Response } from 'express';

/**
 * AllExceptionsFilter - Filtre global qui attrape TOUTES les exceptions
 * 
 * Contrairement a HttpExceptionFilter, ce filter attrape TOUT:
 * - Les HttpException (400, 401, 404, etc.)
 * - Les erreurs JavaScript (TypeError, ReferenceError, etc.)
 * - Les erreurs de base de donnees
 * - N'importe quelle erreur non geree
 * 
 * SECURITE:
 * - Ne JAMAIS exposer les stack traces ou details techniques au client
 * - Toujours logger les erreurs cote serveur pour le debugging
 * 
 * UTILISATION:
 * - Global: app.useGlobalFilters(new AllExceptionsFilter())
 * - Module: { provide: APP_FILTER, useClass: AllExceptionsFilter }
 */

@Catch() // Sans argument = attrape TOUTES les exceptions
export class AllExceptionsFilter implements ExceptionFilter {
  // Logger NestJS pour afficher les erreurs dans la console serveur
  private readonly logger = new Logger(AllExceptionsFilter.name);

  /**
   * Methode appelee automatiquement quand n'importe quelle exception est levee
   * @param exception - L'exception (peut etre n'importe quel type)
   * @param host - ArgumentsHost contenant le contexte de la requete
   */
  catch(exception: unknown, host: ArgumentsHost): void {
    // Recuperer le contexte HTTP (request et response)
    const ctx = host.switchToHttp();
    const response = ctx.getResponse<Response>();
    const request = ctx.getRequest<Request>();

    // Variables pour stocker le status et le message
    let status: number;
    let message: string;

    // Verifier si c'est une HttpException ou une erreur inconnue
    if (exception instanceof HttpException) {
      // CAS 1: C'est une HttpException (erreur HTTP normale)
      status = exception.getStatus();

      // Recuperer le message de l'exception
      const exceptionResponse = exception.getResponse();

      if (typeof exceptionResponse === 'string') {
        message = exceptionResponse;
      } else if (typeof exceptionResponse === 'object' && exceptionResponse !== null) {
        const responseObj = exceptionResponse as Record<string, unknown>;
        message = (responseObj.message as string) || 'An error occurred';
      } else {
        message = 'An error occurred';
      }

      // Logger l'erreur HTTP (niveau warn car c'est "attendu")
      this.logger.warn(`HTTP ${status} | ${request.method} ${request.url} | ${message}`);

    } else {
      // CAS 2: C'est une erreur inattendue (bug, crash, erreur DB, etc.)
      status = HttpStatus.INTERNAL_SERVER_ERROR;

      // Message generique pour le client (ne JAMAIS exposer les details)
      message = 'Internal server error';

      // Logger les details complets cote serveur (pour debugging)
      if (exception instanceof Error) {
        this.logger.error(
          `UNEXPECTED ERROR | ${request.method} ${request.url} | ${exception.message}`,
          exception.stack, // Stack trace visible uniquement dans les logs serveur
        );
      } else {
        this.logger.error(
          `UNEXPECTED ERROR | ${request.method} ${request.url}`,
          String(exception),
        );
      }
    }

    // Construire la reponse d'erreur formatee
    const errorResponse = {
      statusCode: status,
      message: message,
      timestamp: new Date().toISOString(),
      path: request.url,
    };

    // Envoyer la reponse JSON au client
    response.status(status).json(errorResponse);
  }
}
