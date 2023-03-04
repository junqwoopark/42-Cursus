FROM debian:buster

RUN apt-get update && apt-get install -y vsftpd

COPY ./srcs/vsftpd.conf /etc/vsftpd.conf
COPY ./srcs/start.sh /start.sh

RUN chmod +x /start.sh

EXPOSE 20 21 21100-21110

CMD ["/start.sh"]
