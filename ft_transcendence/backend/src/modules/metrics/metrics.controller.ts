/**
 * ============================================
 * METRICS CONTROLLER - Endpoint /metrics
 * ============================================
 * 
 * Ce controller expose l'endpoint GET /api/metrics qui retourne
 * les metriques de l'application au format Prometheus (texte).
 * 
 * Prometheus va scraper cet endpoint automatiquement toutes les X secondes
 * pour collecter les donnees et les stocker dans sa base de donnees.
 * 
 * Ensuite, Grafana peut interroger Prometheus pour afficher
 * des graphiques en temps reel.
 * 
 * Responsable: wtohami- (Backend)
 */

import { Controller, Get, Res } from '@nestjs/common';
import { Response } from 'express';
import { MetricsService } from './metrics.service';

@Controller('metrics')
export class MetricsController {
  constructor(private readonly metricsService: MetricsService) {}

  /**
   * GET /api/metrics
   * Utilise @Res() pour envoyer la reponse directement et contourner
   * le TransformInterceptor global qui enverrait du JSON au lieu du format Prometheus.
   */
  @Get()
  getMetrics(@Res() res: Response): void {
    res.setHeader('Content-Type', 'text/plain; version=0.0.4; charset=utf-8');
    res.send(this.metricsService.getPrometheusMetrics());
  }
}
