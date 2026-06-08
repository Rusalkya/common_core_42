/**
 * ============================================
 * METRICS README - Documentation du système de métriques
 * ============================================
 * 
 * Ce dossier contient le système de collecte de métriques
 * compatible avec Prometheus et Grafana.
 * 
 * Responsable: wtohami- (Backend)
 */

# 📊 Module Metrics - Monitoring Prometheus

Ce module expose les métriques de l'application au format Prometheus pour le monitoring.

## 🎯 Objectif

Permettre au devops de monitorer l'application avec **Prometheus** et **Grafana** en temps réel.

---

## 📡 Endpoint disponible

### `GET /api/metrics`

Retourne les métriques au format texte Prometheus (pas JSON).

**Exemple de réponse :**

```
# HELP http_requests_total Nombre total de requêtes HTTP reçues
# TYPE http_requests_total counter
http_requests_total 1234

# HELP http_errors_total Nombre total d'erreurs HTTP (4xx et 5xx)
# TYPE http_errors_total counter
http_errors_total 42

# HELP http_request_latency_ms Latence moyenne des requêtes HTTP en millisecondes
# TYPE http_request_latency_ms gauge
http_request_latency_ms 125.50

# HELP app_uptime_seconds Temps écoulé depuis le démarrage du serveur en secondes
# TYPE app_uptime_seconds gauge
app_uptime_seconds 3600
```

---

## 📈 Métriques collectées

| Métrique | Type | Description |
|----------|------|-------------|
| `http_requests_total` | Counter | Nombre total de requêtes HTTP reçues |
| `http_errors_total` | Counter | Nombre d'erreurs HTTP (codes >= 400) |
| `http_request_latency_ms` | Gauge | Latence moyenne des requêtes en millisecondes |
| `app_uptime_seconds` | Gauge | Temps écoulé depuis le démarrage du serveur |

---

## 🔧 Architecture

### 1. **MetricsService**
- Stocke les compteurs et latences
- Calcule l'uptime
- Génère le format Prometheus

### 2. **MetricsMiddleware**
- Intercepte chaque requête HTTP
- Mesure la latence
- Enregistre le code de statut

### 3. **MetricsController**
- Expose l'endpoint `GET /api/metrics`
- Retourne le format texte Prometheus

---

## ⚙️ Configuration Prometheus

Ajoute cette configuration dans `monitoring/prometheus/prometheus.yml` :

```yaml
scrape_configs:
  - job_name: 'backend'
    scrape_interval: 15s  # Scraper toutes les 15 secondes
    static_configs:
      - targets: ['backend:3001']  # Remplace par l'URL de ton backend
    metrics_path: '/api/metrics'
```

---

## 📊 Configuration Grafana

1. **Ajouter Prometheus comme datasource**
   - URL: `http://prometheus:9090`

2. **Créer un dashboard avec ces queries**

   - **Requêtes par seconde** :
     ```promql
     rate(http_requests_total[1m])
     ```

   - **Erreurs par seconde** :
     ```promql
     rate(http_errors_total[1m])
     ```

   - **Latence moyenne** :
     ```promql
     http_request_latency_ms
     ```

   - **Uptime** :
     ```promql
     app_uptime_seconds
     ```

---

## ✅ Tester en local

```bash
# Démarrer le backend
npm run start:dev

# Tester l'endpoint metrics
curl http://localhost:3001/api/metrics
```

Tu devrais voir les métriques au format texte Prometheus.

---

## 🚀 Comment ça marche

1. **Chaque requête HTTP** → Le middleware `MetricsMiddleware` l'intercepte
2. **Mesure de latence** → Calcul du temps entre début et fin de requête
3. **Stockage** → Les données sont stockées dans `MetricsService`
4. **Exposition** → Prometheus scrape l'endpoint `/api/metrics` toutes les X secondes
5. **Visualisation** → Grafana interroge Prometheus et affiche les graphiques

---

## 📝 Notes pour le devops

- L'endpoint `/api/metrics` est **public** (pas besoin d'auth)
- Format: **text/plain** (pas JSON)
- Les métriques sont **en mémoire** (réinitialisées au redémarrage)
- Le middleware compte **toutes les routes** (y compris /api/metrics lui-même)

---

## 🐛 Debugging

Si Prometheus ne récupère pas les métriques :

1. Vérifie que l'endpoint fonctionne :
   ```bash
   curl http://localhost:3001/api/metrics
   ```

2. Vérifie les logs Prometheus pour voir s'il arrive à scraper

3. Vérifie la config `scrape_interval` et `metrics_path`

---

**Développé par wtohami- pour l'équipe devops 🚀**
