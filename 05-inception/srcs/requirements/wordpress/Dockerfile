FROM debian:buster

# Dockerfile 작성자
LABEL MAINTAINER="junkpark@student.42seoul.kr"

RUN apt-get update && \
    # apt-get install -y wordpress && \
    apt-get install -y php7.3-fpm

COPY ./conf /etc/php/7.3/fpm/
COPY ./phpinfo.php /var/www/html/

RUN mkdir /run/php

EXPOSE 9000

CMD ["php-fpm7.3", "--nodaemonize"]
# CMD ["service", "php7.3-fpm", "start", "&"]
