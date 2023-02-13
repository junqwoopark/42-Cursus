mysqld &

while [ ! -e /var/run/mysqld/mysqld.sock ]; do
  sleep 1
done

echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';" | mysql -uroot && \
echo "CREATE USER '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';" | mysql -uroot -p${MYSQL_ROOT_PASSWORD} && \
echo "GRANT ALL PRIVILEGES ON *.* TO '${MYSQL_USER}'@'%';" | mysql -uroot -p${MYSQL_ROOT_PASSWORD} && \
echo "CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};" | mysql -u root --password=${MYSQL_ROOT_PASSWORD}

pkill mysqld
mysqld
