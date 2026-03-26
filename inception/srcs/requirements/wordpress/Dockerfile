FROM debian:buster

RUN sed -i 's|deb.debian.org/debian|archive.debian.org/debian|g' /etc/apt/sources.list \
    && sed -i 's|security.debian.org/debian-security|archive.debian.org/debian-security|g' /etc/apt/sources.list \
    && sed -i '/buster-updates/d' /etc/apt/sources.list \
    && echo 'Acquire::Check-Valid-Until "false";' > /etc/apt/apt.conf.d/99no-check-valid

RUN apt-get update && apt-get install -y \
    php \
    php-fpm \
    php-mysql \
    curl \
    mariadb-client

RUN curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -o /usr/local/bin/wp \
    && chmod +x /usr/local/bin/wp

RUN mkdir -p /run/php

COPY conf/www.conf /etc/php/7.3/fpm/pool.d/www.conf
COPY tools/setup.sh /setup.sh

RUN chmod +x /setup.sh

WORKDIR /var/www/html

CMD ["/setup.sh"]
