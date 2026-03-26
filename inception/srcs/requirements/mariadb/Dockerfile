FROM debian:buster

RUN sed -i 's|deb.debian.org/debian|archive.debian.org/debian|g' /etc/apt/sources.list \
	&& sed -i 's|security.debian.org/debian-security|archive.debian.org/debian-security|g' /etc/apt/sources.list \
	&& sed -i '/buster-updates/d' /etc/apt/sources.list \
	&& echo 'Acquire::Check-Valid-Until "false";' > /etc/apt/apt.conf.d/99no-check-valid

RUN apt-get update && apt-get install -y mariadb-server

COPY conf/my.cnf /etc/mysql/my.cnf
COPY tools/init.sh /init.sh

RUN chmod +x /init.sh

CMD ["/init.sh"]
