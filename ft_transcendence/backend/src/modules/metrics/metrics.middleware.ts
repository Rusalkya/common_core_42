/**
 * ============================================
 * METRICS MIDDLEWARE - Intercepte les requetes HTTP
 * ============================================
 * 
 * Ce middleware s'execute avant et apres chaque requete HTTP
 * pour enregistrer les metriques :
 * - Temps de debut de la requete
 * - Code de statut de la reponse
 * - Latence (temps de traitement)
 * 
 * Les donnees sont ensuite envoyees au MetricsService.
 * 
 * Responsable: wtohami- (Backend)
 */

import { Injectable, NestMiddleware } from '@nestjs/common';
import { Request, Response, NextFunction } from 'express';
import { MetricsService } from './metrics.service';

@Injectable()
export class MetricsMiddleware implements NestMiddleware {
  constructor(private readonly metricsService: MetricsService) {}

  /**
   * Methode appelee pour chaque requete HTTP
   */
  use(req: Request, res: Response, next: NextFunction): void {
    // Enregistrer le temps de debut de la requete
    const startTime = Date.now();

    // Ecouter l'evenement 'finish' qui se declenche quand la reponse est envoyee
    res.on('finish', () => {
      // Calculer la latence en millisecondes
      const latency = Date.now() - startTime;

      // Recuperer le code de statut HTTP de la reponse
      const statusCode = res.statusCode;

      // Enregistrer les metriques dans le service
      this.metricsService.recordRequest(statusCode, latency);
    });

    // Passer au middleware suivant
    next();
  }
}
