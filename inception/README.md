*This project has been created as part of the 42 curriculum by clfouger*

# Inception

## Description
This project builds a small production-like web infrastructure with Docker Compose.
It runs three isolated services:
- NGINX as the only external entrypoint on HTTPS port 443
- WordPress with PHP-FPM
- MariaDB for persistent database storage

The main goal is to design reproducible infrastructure from custom Dockerfiles, with service isolation, secure communication (TLS), and persistent data.

## Project Description
### How Docker is used in this project
Docker is used to package each service with its own dependencies and runtime configuration.
Each service has its own Dockerfile and startup script under srcs/requirements.
Docker Compose then orchestrates all services together, including network, secrets, and volumes.

### Main design choices
- Debian buster base images for all services
- One container per service
- HTTPS only through NGINX on port 443
- Shared internal bridge network for inter-service communication
- Persistent data mapped under /home/vboxuser/data
- Credentials stored with Docker secrets, not plain Dockerfile values

### Sources included in the repository
- srcs/docker-compose.yml for orchestration
- srcs/requirements/mariadb for database image, config, and init script
- srcs/requirements/wordpress for WordPress image, PHP-FPM config, and setup script
- srcs/requirements/nginx for reverse proxy image, TLS cert generation, and web config
- secrets directory for local secret files used by Docker Compose
- Makefile for build and lifecycle shortcuts

### Comparisons required by the subject
#### Virtual Machines vs Docker
- VM: includes full guest OS, heavier, slower startup, higher resource cost.
- Docker: process-level isolation on the host kernel, lighter, faster startup, easier reproducibility.

#### Secrets vs Environment Variables
- Environment variables are convenient but can be exposed in process metadata or logs.
- Docker secrets are mounted as files at runtime, reducing accidental exposure of sensitive values.

#### Docker Network vs Host Network
- Docker bridge network isolates services and allows name-based service discovery (mariadb, wordpress, nginx).
- Host network removes isolation and can create port conflicts and weaker boundaries.

#### Docker Volumes vs Bind Mounts
- Named volumes are managed by Docker and are portable and predictable.
- Bind mounts map host paths directly; useful here to satisfy the project rule requiring data under /home/login/data.

## Instructions
### Prerequisites
- Docker Engine with Compose plugin
- Linux VM environment recommended by the subject
- Domain mapping in /etc/hosts (example: 127.0.0.1 clfouger.42.fr)

### Build and run
From repository root:
- make

### Stop stack
From repository root:
- make clean

### Full cleanup and rebuild
From repository root:
- make re

### Access
- Website: https://clfouger.42.fr
- Admin: https://clfouger.42.fr/wp-admin

### Mandatory checks examples
- HTTP port 80 must fail: curl -I --max-time 5 http://localhost
- TLS 1.2: echo | openssl s_client -connect localhost:443 -tls1_2
- TLS 1.3: echo | openssl s_client -connect localhost:443 -tls1_3
- Volumes path check: docker volume inspect srcs_mariadb_data srcs_wordpress_data

## Resources
- Docker documentation: https://docs.docker.com/
- Docker Compose file reference: https://docs.docker.com/compose/compose-file/
- NGINX documentation: https://nginx.org/en/docs/
- WordPress CLI documentation: https://developer.wordpress.org/cli/commands/
- MariaDB documentation: https://mariadb.com/kb/en/documentation/
- 42 Inception community tutorial: https://tuto.grademe.fr/inception/

### How AI was used
AI was used as a support tool for:
- Reviewing configuration consistency across Docker, NGINX, MariaDB, and WordPress files
- Explaining subject constraints and evaluator checklist items in simple language
- Suggesting shell commands for verification and debugging

All generated suggestions were manually reviewed, adapted, and tested before being kept in the project.
