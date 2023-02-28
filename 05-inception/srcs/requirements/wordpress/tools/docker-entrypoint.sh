#!/bin/sh

set -e

if [ ! -f /var/www/html/index.php ]; then
  mkdir -p /var/www/html
  chown -R www-data:www-data /var/www/html

  wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
  chmod +x wp-cli.phar
  mv wp-cli.phar /usr/local/bin/wp
  wp core download --allow-root
  wp config create --dbname=$MYSQL_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=db --allow-root
  wp core install --url=https://junkpark.42.fr --title="JunkPark" --admin_user=$WP_USER --admin_password=$WP_PASSWORD --admin_email=$WP_EMAIL --skip-email --allow-root
fi

exec "php-fpm7.3" "-F"
