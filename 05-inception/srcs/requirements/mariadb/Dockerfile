FROM debian:buster

LABEL MAINTAINER="junkpark@student.42seoul.kr"

RUN apt-get update && \
    apt-get install -y mariadb-server && \
    mkdir /var/run/mysqld && \
    chown -R mysql:mysql /var/run/mysqld

ENV MYSQL_ROOT_PASSWORD=junkpark
ENV MYSQL_DATABASE=junkpark
ENV MYSQL_USER=junkpark
ENV MYSQL_PASSWORD=junkpark

RUN apt-get install -y procps

COPY ./tools/docker-entrypoint.sh /usr/local/bin/

# CMD ["mysqld"]
# Start the MariaDB server
ENTRYPOINT [ "sh",  "/usr/local/bin/docker-entrypoint.sh" ]

# # Start the MariaDB server
# CMD ["mysqld"]

# # Set the root password
# RUN service mysql start && \
#     mysql -uroot -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';"

# # Create a new user
# RUN service mysql start && \
#     mysql -uroot -p${MYSQL_ROOT_PASSWORD} -e "CREATE USER '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';" && \
#     mysql -uroot -p${MYSQL_ROOT_PASSWORD} -e "GRANT ALL PRIVILEGES ON *.* TO '${MYSQL_USER}'@'%';"



# RUN echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';" | mysql -uroot && \
#     echo "CREATE USER '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';" | mysql -uroot -p${MYSQL_ROOT_PASSWORD} && \
#     echo "GRANT ALL PRIVILEGES ON *.* TO '${MYSQL_USER}'@'%';" | mysql -uroot -p${MYSQL_ROOT_PASSWORD} && \
#     echo "CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};" | mysql -u root --password=${MYSQL_ROOT_PASSWORD} && \
#     echo "GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';" | mysql -u root --password=${MYSQL_ROOT_PASSWORD}


