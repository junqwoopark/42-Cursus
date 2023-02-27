FROM debian:buster

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y nginx && \
    apt-get install -y openssl

COPY ./conf/default /etc/nginx/sites-available/

COPY ./tools/ssl-keygen.sh /tmp/ssl-keygen.sh
RUN sh /tmp/ssl-keygen.sh

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
