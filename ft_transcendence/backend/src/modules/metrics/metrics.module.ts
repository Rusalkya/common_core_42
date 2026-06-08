/**
 * ============================================
 * METRICS MODULE - Module de metriques Prometheus
 * ============================================
 * 
 * Ce module regroupe tout le systeme de metriques :
 * - MetricsService : Stocke et calcule les metriques
 * - MetricsController : Expose l'endpoint /api/metrics
 * - MetricsMiddleware : Intercepte les requetes HTTP
 * 
 * Le middleware est applique globalement dans app.module.ts
 * 
 * Responsable: wtohami- (Backend)
 */

import { Module } from '@nestjs/common';
import { MetricsService } from './metrics.service';
import { MetricsController } from './metrics.controller';

@Module({
  controllers: [MetricsController],
  providers: [MetricsService],
  exports: [MetricsService], // Exporter pour utiliser dans app.module.ts
})
export class MetricsModule {}
