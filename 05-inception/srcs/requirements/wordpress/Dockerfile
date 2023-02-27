FROM debian:buster

RUN apt-get update && \
    apt-get install -y php7.3-fpm && \
    apt-get install -y php-mysql && \
    apt-get install -y mariadb-client && \
    apt-get install -y wget && \
    apt-get install -y sudo

COPY ./conf/www.conf /etc/php/7.3/fpm/pool.d/

WORKDIR /var/www/html
COPY ./tools/wordpress-setup.sh /tmp/wordpress-setup.sh

RUN mkdir /run/php

EXPOSE 9000

ENTRYPOINT [ "sh", "/tmp/wordpress-setup.sh" ]
