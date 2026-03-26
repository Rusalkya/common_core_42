# Developer Documentation

## Prerequisites
- Linux VM environment
- Docker Engine installed
- Docker Compose plugin available as docker compose
- Local domain mapped in /etc/hosts (example: 127.0.0.1 clfouger.42.fr)

## Repository layout
- srcs/docker-compose.yml: orchestration
- srcs/.env: non-secret environment configuration
- srcs/requirements/mariadb: MariaDB image and bootstrap script
- srcs/requirements/wordpress: WordPress image and setup logic
- srcs/requirements/nginx: NGINX image and TLS reverse proxy config
- secrets: local secret files consumed by Compose
- Makefile: top-level commands

## Setup
From repository root:
- make

This command creates host data directories and starts all services with build.

## Makefile usage
- make: build and start stack
- make clean: stop and remove containers/network
- make fclean: aggressive Docker cleanup
- make re: full cleanup then rebuild

## Docker Compose usage
From repository root:
- docker compose -f srcs/docker-compose.yml up -d --build
- docker compose -f srcs/docker-compose.yml down
- docker compose -f srcs/docker-compose.yml ps
- docker compose -f srcs/docker-compose.yml logs -f

## Data persistence
Persistent data is stored through volumes configured in Compose and mapped to:
- /home/vboxuser/data/mariadb
- /home/vboxuser/data/wordpress

Check volume bindings:
- docker volume inspect srcs_mariadb_data srcs_wordpress_data

## Notes on service design
- NGINX is the only public entrypoint, exposing port 443 only.
- WordPress is internal and reachable through fastcgi from NGINX.
- MariaDB is internal and reachable from WordPress only through the internal network.
- Credentials are loaded from mounted secret files at runtime.

## Troubleshooting
### Domain not reachable
- Verify /etc/hosts entry for clfouger.42.fr
- Check service status with docker compose ps

### HTTP opens unexpectedly
- Confirm only 443 is published in srcs/docker-compose.yml
- Check with curl -I --max-time 5 http://localhost

### WordPress setup issues
- Check logs: docker compose -f srcs/docker-compose.yml logs wordpress mariadb
- Verify database user and grants inside MariaDB
