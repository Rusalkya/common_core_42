import {
  ExceptionFilter,
  Catch,
  ArgumentsHost,
  HttpException,
  Logger,
} from '@nestjs/common';
import { Request, Response } from 'express';

/**
 * HttpExceptionFilter - Filtre pour les exceptions HTTP
 * 
 * Ce filter attrape uniquement les HttpException (400, 401, 403, 404, etc.)
 * et formate la reponse de maniere uniforme pour le client.
 * 
 * UTILISATION:
 * - Global: app.useGlobalFilters(new HttpExceptionFilter())
 * - Module: { provide: APP_FILTER, useClass: HttpExceptionFilter }
 * - Controller/Route: @UseFilters(HttpExceptionFilter)
 */

@Catch(HttpException) // Attrape uniquement les HttpException
export class HttpExceptionFilter implements ExceptionFilter {
  // Logger NestJS pour afficher les erreurs dans la console serveur
  private readonly logger = new Logger(HttpExceptionFilter.name);

  /**
   * Methode appelee automatiquement quand une HttpException est levee
   * @param exception - L'exception HTTP qui a ete levee
   * @param host - ArgumentsHost contenant le contexte de la requete
   */
  catch(exception: HttpException, host: ArgumentsHost): void {
    // Recuperer le contexte HTTP (request et response)
    const ctx = host.switchToHttp();
    const response = ctx.getResponse<Response>();
    const request = ctx.getRequest<Request>();

    // Recuperer le code de status HTTP (400, 401, 404, 500, etc.)
    const status = exception.getStatus();

    // Recuperer la reponse de l'exception
    // Peut etre un string: "Not Found"
    // Ou un objet: { message: "User not found", error: "Not Found", statusCode: 404 }
    const exceptionResponse = exception.getResponse();

    // Extraire le message d'erreur
    let message: string | string[];
    let error: string;

    if (typeof exceptionResponse === 'string') {
      // Cas simple: la reponse est directement un string
      message = exceptionResponse;
      error = exceptionResponse;
    } else if (typeof exceptionResponse === 'object' && exceptionResponse !== null) {
      // Cas objet: extraire message et error
      const responseObj = exceptionResponse as Record<string, unknown>;
      message = (responseObj.message as string | string[]) || 'An error occurred';
      error = (responseObj.error as string) || 'Error';
    } else {
      message = 'An error occurred';
      error = 'Error';
    }

    // Logger l'erreur cote serveur (pour le debugging)
    this.logger.warn(
      `HTTP ${status} | ${request.method} ${request.url} | ${JSON.stringify(message)}`,
    );

    // Construire la reponse d'erreur formatee
    const errorResponse = {
      statusCode: status,
      message: message,
      error: error,
      timestamp: new Date().toISOString(),
      path: request.url,
    };

    // Envoyer la reponse JSON au client
    response.status(status).json(errorResponse);
  }
}
