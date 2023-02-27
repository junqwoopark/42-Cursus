FROM	debian:buster

RUN		apt-get update -y && \
		apt-get upgrade -y && \
		apt-get -y install \
		mariadb-server \
		mariadb-client

COPY	./conf/50-server.cnf /etc/mysql/mariadb.conf.d/

COPY	./tools/docker-entrypoint.sh /tmp/mariadb_setup.sh

EXPOSE 3306

ENTRYPOINT ["sh", "/tmp/mariadb_setup.sh"]
