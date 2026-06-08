/**
 * ============================================
 * METRICS SERVICE - Collecte des metriques Prometheus
 * ============================================
 * 
 * Ce service stocke et calcule les metriques de l'application :
 * - Nombre total de requetes HTTP
 * - Nombre d'erreurs (4xx et 5xx)
 * - Latence moyenne des requetes
 * - Uptime du serveur
 * 
 * Ces metriques sont exposees au format Prometheus (texte)
 * pour etre scrapees par Prometheus et visualisees dans Grafana.
 * 
 * Responsable: wtohami- (Backend)
 * Demande par: DevOps team
 */

import { Injectable } from '@nestjs/common';

@Injectable()
export class MetricsService {
  // Temps de demarrage du serveur (pour calculer l'uptime)
  private readonly startTime: number = Date.now();

  // Compteur total de requetes HTTP
  private requestCount: number = 0;

  // Compteur d'erreurs (codes 4xx et 5xx)
  private errorCount: number = 0;

  // Tableau des latences pour calculer la moyenne
  private latencies: number[] = [];

  // Limite du tableau de latences (garder les 1000 dernieres)
  private readonly MAX_LATENCIES = 1000;

  /**
   * Enregistre une nouvelle requete HTTP
   * @param statusCode - Code HTTP de la reponse (200, 404, 500, etc.)
   * @param latency - Temps de traitement en millisecondes
   */
  recordRequest(statusCode: number, latency: number): void {
    // Incrementer le compteur total de requetes
    this.requestCount++;

    // Si c'est une erreur (code >= 400), incrementer le compteur d'erreurs
    if (statusCode >= 400) {
      this.errorCount++;
    }

    // Ajouter la latence au tableau
    this.latencies.push(latency);

    // Limiter la taille du tableau pour eviter la surcharge memoire
    if (this.latencies.length > this.MAX_LATENCIES) {
      this.latencies.shift(); // Retirer la plus ancienne
    }
  }

  /**
   * Calcule la latence moyenne en millisecondes
   */
  getAverageLatency(): number {
    if (this.latencies.length === 0) {
      return 0;
    }

    const sum = this.latencies.reduce((acc, latency) => acc + latency, 0);
    return sum / this.latencies.length;
  }

  /**
   * Calcule l'uptime du serveur en secondes
   */
  getUptime(): number {
    return Math.floor((Date.now() - this.startTime) / 1000);
  }

  /**
   * Genere les metriques au format Prometheus (texte)
   * 
   * Format Prometheus :
   * # HELP nom_metrique Description de la metrique
   * # TYPE nom_metrique type (counter, gauge, histogram, etc.)
   * nom_metrique valeur
   * 
   * @returns String au format Prometheus
   */
  getPrometheusMetrics(): string {
    const metrics: string[] = [];

    // 1. Nombre total de requetes HTTP
    metrics.push('# HELP http_requests_total Nombre total de requetes HTTP recues');
    metrics.push('# TYPE http_requests_total counter');
    metrics.push(`http_requests_total ${this.requestCount}`);
    metrics.push('');

    // 2. Nombre d'erreurs HTTP (codes >= 400)
    metrics.push('# HELP http_errors_total Nombre total d\'erreurs HTTP (4xx et 5xx)');
    metrics.push('# TYPE http_errors_total counter');
    metrics.push(`http_errors_total ${this.errorCount}`);
    metrics.push('');

    // 3. Latence moyenne des requetes en millisecondes
    metrics.push('# HELP http_request_latency_ms Latence moyenne des requetes HTTP en millisecondes');
    metrics.push('# TYPE http_request_latency_ms gauge');
    metrics.push(`http_request_latency_ms ${this.getAverageLatency().toFixed(2)}`);
    metrics.push('');

    // 4. Uptime du serveur en secondes
    metrics.push('# HELP app_uptime_seconds Temps ecoule depuis le demarrage du serveur en secondes');
    metrics.push('# TYPE app_uptime_seconds gauge');
    metrics.push(`app_uptime_seconds ${this.getUptime()}`);
    metrics.push('');

    // Joindre toutes les lignes avec des retours a la ligne
    return metrics.join('\n');
  }

  /**
   * Reinitialise toutes les metriques (utile pour les tests)
   */
  reset(): void {
    this.requestCount = 0;
    this.errorCount = 0;
    this.latencies = [];
  }
}
