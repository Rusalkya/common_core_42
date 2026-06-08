.PHONY: help up down db backend frontend install logs clean re fclean docker

# ========================================
# AIDE
# ========================================

help:
	@echo "FT_TRANSCENDENCE - Commandes"
	@echo ""
	@echo "Principal:"
	@echo "  make up            - Tout lancer en mode DEV (npm local + db Docker)"
	@echo "  make docker        - Tout lancer en mode PROD (Docker Compose complet)"
	@echo "  make down          - Tout arreter"
	@echo "  make re            - Relancer tout (down + up)"
	@echo ""
	@echo "Services individuels:"
	@echo "  make db            - Lancer uniquement la base de donnees"
	@echo "  make backend       - Lancer uniquement le backend (dev)"
	@echo "  make frontend      - Lancer uniquement le frontend (dev)"
	@echo ""
	@echo "Utilitaires:"
	@echo "  make install       - Installer les dependances npm"
	@echo "  make logs          - Logs de tous les conteneurs Docker"
	@echo "  make logs-back     - Logs du backend (npm dev)"
	@echo "  make logs-front    - Logs du frontend (vite)"
	@echo "  make clean         - Supprimer node_modules et dist"
	@echo "  make fclean        - TOUT supprimer (conteneurs, images, volumes, cache...)"
	@echo ""
	@echo "URLs:"
	@echo "  Backend    -> http://localhost:3001/api"
	@echo "  Swagger    -> http://localhost:3001/api/docs"
	@echo "  Frontend   -> http://localhost:3000"
	@echo "  Prometheus -> http://localhost:9090"
	@echo "  Grafana    -> http://localhost:3003"
	@echo ""

# ========================================
# MODE PROD - Docker Compose complet
# ========================================


certs:
	@sh nginx/generate-cert.sh

docker: certs
	@echo "=== MODE PROD - Docker Compose ==="
	@docker rm -f nginx frontend backend db prometheus grafana 2>/dev/null || true
	@docker compose up --build
docker-down:
	@docker compose down

# ========================================
# MODE DEV - npm local + db Docker
# ========================================

up: install docker-up wait-db migrate
	@echo "Lancement du backend (mode dev)..."
	@fuser -k 3001/tcp > /dev/null 2>&1 || true
	@fuser -k 3000/tcp > /dev/null 2>&1 || true
	@cd backend && npm run start:dev > /tmp/backend.log 2>&1 & echo $$! > /tmp/backend.pid
	@echo "Attente du backend (http://localhost:3001/api/health)..."
	@for i in $$(seq 1 40); do \
		if curl -sf http://localhost:3001/api/health > /dev/null 2>&1; then \
			echo "Backend pret"; break; \
		fi; \
		sleep 2; \
		if [ $$i -eq 40 ]; then echo "Backend timeout - voir /tmp/backend.log"; fi; \
	done
	@echo "Lancement du frontend (mode dev)..."
	@cd frontend && npm run dev > /tmp/frontend.log 2>&1 & echo $$! > /tmp/frontend.pid
	@sleep 3
	@echo ""
	@echo "Tout est lance !"
	@echo "  Backend    -> http://localhost:3001/api"
	@echo "  Swagger    -> http://localhost:3001/api/docs"
	@echo "  Frontend   -> http://localhost:3000"
	@echo "  Prometheus -> http://localhost:9090"
	@echo "  Grafana    -> http://localhost:3003"
	@echo ""
	@echo "Logs backend : make logs-back"
	@echo "Logs frontend: make logs-front"
	@echo "Logs Docker  : make logs"

docker-up:
	@echo "Lancement des services Docker (db, prometheus, grafana)..."
	podman-compose up db prometheus grafana --no-deps -d
	@echo "Conteneurs lances"

# ========================================
# TOUT ARRETER
# ========================================

down:
	@echo "Arret des services..."
	@if [ -f /tmp/backend.pid ]; then kill $$(cat /tmp/backend.pid) 2>/dev/null || true; rm -f /tmp/backend.pid; fi
	@if [ -f /tmp/frontend.pid ]; then kill $$(cat /tmp/frontend.pid) 2>/dev/null || true; rm -f /tmp/frontend.pid; fi
	@pkill -f "[n]est start" 2>/dev/null || true
	@pkill -f "[v]ite" 2>/dev/null || true
	@pkill -f "[e]sbuild" 2>/dev/null || true
	@podman-compose down 2>/dev/null || true
	@docker compose down --timeout 10 2>/dev/null || true
	@echo "Tout est arrete"

re: down up

# ========================================
# BASE DE DONNEES SEULE
# ========================================

db:
	@echo "Lancement de la base de donnees PostgreSQL..."
	podman-compose up db -d
	@echo "Conteneur db lance"

wait-db:
	@echo "Attente que PostgreSQL soit healthy..."
	@for i in $$(seq 1 30); do \
		STATUS=$$(podman inspect --format='{{.State.Health.Status}}' db 2>/dev/null); \
		if [ "$$STATUS" = "healthy" ]; then \
			echo "PostgreSQL est pret"; break; \
		fi; \
		echo "  Etat: $$STATUS ($$i/30)..."; \
		sleep 2; \
		if [ $$i -eq 30 ]; then echo "PostgreSQL timeout"; exit 1; fi; \
	done

# ========================================
# MIGRATIONS PRISMA
# ========================================

migrate:
	@echo "Application des migrations Prisma..."
	@cd backend && npx prisma migrate deploy 2>&1 | tee /tmp/prisma.log; \
	if grep -q "P3005" /tmp/prisma.log; then \
		echo "DB non vide detectee, baseline des migrations..."; \
		npx prisma migrate resolve --applied 20260422115947_init 2>/dev/null || true; \
		npx prisma migrate resolve --applied 20260518090256_add_repost_model 2>/dev/null || true; \
		npx prisma migrate resolve --applied 20260520120000_add_notification_types 2>/dev/null || true; \
		npx prisma migrate deploy; \
	fi
	@echo "Migrations appliquees"

# ========================================
# SERVICES INDIVIDUELS (mode dev)
# ========================================

backend: wait-db migrate
	@echo "Demarrage du backend..."
	@echo "Backend: http://localhost:3001/api"
	cd backend && npm run start:dev

frontend:
	@echo "Demarrage du frontend..."
	@echo "Frontend: http://localhost:3000"
	cd frontend && npm run dev

# ========================================
# INSTALLATION DES DEPENDANCES
# ========================================

install:
	@echo "Installation des dependances backend..."
	cd backend && npm install
	@echo "Installation des dependances frontend..."
	cd frontend && npm install
	@echo "Dependances installees"

# ========================================
# LOGS
# ========================================

logs:
	@echo "Logs Docker (tous les services):"
	podman-compose logs -f

logs-back:
	@tail -f /tmp/backend.log

logs-front:
	@tail -f /tmp/frontend.log

# ========================================
# NETTOYAGE
# ========================================

clean:
	@echo "Suppression de node_modules et dist..."
	rm -rf backend/node_modules backend/dist
	rm -rf frontend/node_modules frontend/dist
	@echo "Nettoyage termine"

fclean: down clean
	@echo "=== NETTOYAGE COMPLET ==="
	@docker compose down -v --remove-orphans 2>/dev/null || true
	@echo "Suppression de tous les conteneurs..."
	@docker ps -aq | xargs -r docker rm -f 2>/dev/null || true
	@echo "Suppression de tous les volumes..."
	@docker volume ls -q | xargs -r docker volume rm -f 2>/dev/null || true
	@echo "Suppression de tous les reseaux custom..."
	@docker network ls --format '{{.Name}}' | grep -v -E '^(bridge|host|none)$$' | xargs -r docker network rm 2>/dev/null || true
	@echo "Suppression de toutes les images..."
	@docker images -q | xargs -r docker rmi -f 2>/dev/null || true
	@echo "Suppression des logs tmp..."
	@rm -f /tmp/backend.log /tmp/frontend.log /tmp/prisma.log /tmp/backend.pid /tmp/frontend.pid
	@echo ""
	@echo "=== TOUT EST SUPPRIME ==="
# ========================================
# PAR DEFAUT
# ========================================

.DEFAULT_GOAL := help