FROM debian:buster

RUN apt-get update && \
    apt-get install -y php7.3-fpm && \
    apt-get install -y php-mysql && \
    apt-get install -y mariadb-client && \
    apt-get install -y wget && \
    apt-get install -y sudo

RUN mkdir /run/php

COPY ./conf/www.conf /etc/php/7.3/fpm/pool.d/
COPY ./tools/docker-entrypoint.sh /usr/local/bin/
COPY ./tools/adminer.php /var/www/html/

WORKDIR /var/www/html/

EXPOSE 9000

ENTRYPOINT [ "docker-entrypoint.sh" ]
