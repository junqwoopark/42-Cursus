#!/bin/sh

set -e

if [ ! -f /var/www/html/index.php ]; then
    mkdir -p /var/www/html
    chown -R www-data:www-data /var/www/html

    wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
    chmod +x wp-cli.phar
    mv wp-cli.phar /usr/local/bin/wp
    wp core download --path=/var/www/html --allow-root
    wp config create --path=/var/www/html --dbname=$MYSQL_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=db --allow-root
    wp core install --path=/var/www/html --url=junkpark.42.fr --title=JunkPark --admin_user=admin --admin_password=admin --admin_email=admin@google.com --allow-root
fi

exec "php-fpm7.3" "-F"
