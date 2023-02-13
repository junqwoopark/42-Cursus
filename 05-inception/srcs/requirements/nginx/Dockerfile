FROM debian:buster

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y nginx && \
    apt-get install -y openssl

RUN mkdir /root/ssl

RUN openssl req -x509 -days 30 -nodes -newkey rsa:2048 -subj "/C=KR/ST=Seoul/L=Seoul/O=42seoul/OU=Cadet/CN=localhost"\
   -keyout /root/ssl/nginx-ssl.key -out /root/ssl/nginx-ssl.crt

EXPOSE 443

COPY ./conf /etc/nginx/

CMD ["nginx", "-g", "daemon off;"]
