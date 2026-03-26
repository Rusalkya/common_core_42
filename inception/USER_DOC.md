# User Documentation

## Purpose
This document explains how an end user or administrator can run and use the website.

## Start the stack
From repository root:
- make

## Stop the stack
From repository root:
- make clean

## Access URLs
- Public site: https://clfouger.42.fr
- Admin dashboard: https://clfouger.42.fr/wp-admin

If the domain does not resolve, add this line to /etc/hosts:
- 127.0.0.1 clfouger.42.fr

## Credentials management
Credentials are loaded from Docker secrets files in the secrets directory.

Main files:
- secrets/wp_admin_password.txt
- secrets/wp_user_password.txt
- secrets/db_password.txt
- secrets/db_root_password.txt

After changing a secret, recreate services:
- make re

## Basic checks
### Site must be HTTPS-only
- curl -I --max-time 5 http://localhost
Expected: connection refused or failure on port 80.

### TLS support
- echo | openssl s_client -connect localhost:443 -tls1_2
- echo | openssl s_client -connect localhost:443 -tls1_3
Expected: successful handshake for both versions.

### Containers status
- docker compose -f srcs/docker-compose.yml ps
Expected: mariadb, wordpress, and nginx are up.

## Edit a page during evaluation
1. Sign in as admin at /wp-admin.
2. Open Pages and edit an existing page.
3. Save or update.
4. Refresh the public website and confirm the content changed.
