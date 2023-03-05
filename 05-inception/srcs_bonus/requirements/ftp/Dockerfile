FROM debian:buster

RUN apt-get update && apt-get install -y vsftpd

COPY ./conf/vsftpd.conf /etc/vsftpd/
COPY ./conf/vsftpd_virtual /etc/pam.d/
COPY ./tools/docker-entrypoint.sh /usr/local/bin

RUN chmod +x /start.sh

EXPOSE 20 21 21100-21110

CMD ["/start.sh"]
