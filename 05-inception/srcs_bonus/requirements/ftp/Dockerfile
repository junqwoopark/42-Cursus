FROM debian:buster

RUN apt-get update && apt-get install -y vsftpd db-util

COPY ./conf/vsftpd.conf /etc/
COPY ./conf/vsftpd_virtual /etc/pam.d/
COPY ./tools/docker-entrypoint.sh /usr/local/bin

RUN chmod +x /usr/local/bin/docker-entrypoint.sh

ENV FTP_USER ftp
ENV FTP_PASS ftp
ENV PASV_MIN_PORT 21100
ENV PASV_MAX_PORT 21110

EXPOSE 20 21

ENTRYPOINT ["docker-entrypoint.sh"]
