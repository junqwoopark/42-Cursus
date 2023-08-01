FROM debian:bullseye

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y nginx && \
    apt-get install -y openssl

COPY ./conf/default /etc/nginx/sites-available/

COPY ./tools/ssl-keygen.sh /usr/local/bin/
RUN ssl-keygen.sh

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
