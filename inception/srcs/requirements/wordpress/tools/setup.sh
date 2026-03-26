#!/bin/sh
set -e

mkdir -p /run/php
cd /var/www/html

if [ -n "${MYSQL_PASSWORD_FILE:-}" ] && [ -f "${MYSQL_PASSWORD_FILE}" ]; then
    MYSQL_PASSWORD="$(cat "${MYSQL_PASSWORD_FILE}")"
fi

if [ -n "${WP_ADMIN_PASSWORD_FILE:-}" ] && [ -f "${WP_ADMIN_PASSWORD_FILE}" ]; then
    WP_ADMIN_PASSWORD="$(cat "${WP_ADMIN_PASSWORD_FILE}")"
fi

if [ -n "${WP_USER_PASSWORD_FILE:-}" ] && [ -f "${WP_USER_PASSWORD_FILE}" ]; then
    WP_USER_PASSWORD="$(cat "${WP_USER_PASSWORD_FILE}")"
fi

if [ ! -f wp-config.php ]; then
    echo "Installing WordPress core..."
    curl -fsSL https://wordpress.org/latest.tar.gz -o latest.tar.gz
    tar -xzf latest.tar.gz --strip-components=1
    rm -f latest.tar.gz
    chown -R www-data:www-data /var/www/html
fi

echo "Waiting for MariaDB..."
i=0
until mysqladmin ping -h"mariadb" -u"${MYSQL_USER}" -p"${MYSQL_PASSWORD}" --silent; do
    i=$((i + 1))
    if [ "$i" -ge 60 ]; then
        echo "MariaDB did not become ready in time"
        exit 1
    fi
    sleep 2
done

if [ ! -f wp-config.php ]; then
    wp config create \
        --allow-root \
        --path=/var/www/html \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_PASSWORD}" \
        --dbhost="mariadb:3306"
fi

if ! wp core is-installed --allow-root --path=/var/www/html >/dev/null 2>&1; then
    wp core install \
        --allow-root \
        --path=/var/www/html \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --skip-email

    wp user create "${WP_USER}" "${WP_USER_EMAIL}" \
        --allow-root \
        --path=/var/www/html \
        --role=author \
        --user_pass="${WP_USER_PASSWORD}"
fi

exec php-fpm7.3 -F

