FROM debian:buster

# Dockerfile 작성자
LABEL MAINTAINER="junkpark@student.42seoul.kr"

RUN apt-get update && \
    apt-get install -y php7.3-fpm && \
    apt-get install -y php-mysql && \
    apt-get install -y wget

RUN wget https://wordpress.org/latest.tar.gz && \
    tar xzvf latest.tar.gz && \
    mkdir -p /var/www/html && \
    cp -r wordpress /var/www/html/ && \
    chown -R www-data:www-data /var/www/html/wordpress

COPY ./conf /etc/php/7.3/fpm/

RUN mkdir /run/php

EXPOSE 9000

CMD ["php-fpm7.3", "--nodaemonize"]
# CMD ["service", "php7.3-fpm", "start", "&"]
