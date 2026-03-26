#!/bin/sh
set -e

mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld /var/lib/mysql

if [ -n "${MYSQL_PASSWORD_FILE:-}" ] && [ -f "${MYSQL_PASSWORD_FILE}" ]; then
    MYSQL_PASSWORD="$(cat "${MYSQL_PASSWORD_FILE}")"
fi

if [ -n "${MYSQL_ROOT_PASSWORD_FILE:-}" ] && [ -f "${MYSQL_ROOT_PASSWORD_FILE}" ]; then
    MYSQL_ROOT_PASSWORD="$(cat "${MYSQL_ROOT_PASSWORD_FILE}")"
fi

if [ ! -d "/var/lib/mysql/mysql" ]; then
    mariadb-install-db --user=mysql --datadir=/var/lib/mysql >/dev/null
fi

cat > /tmp/init.sql <<EOF
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF

exec mysqld --user=mysql --init-file=/tmp/init.sql
