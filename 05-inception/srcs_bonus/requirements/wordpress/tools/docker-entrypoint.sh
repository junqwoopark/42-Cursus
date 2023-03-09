#!/bin/sh

set -e

if [ ! -f /var/www/html/index.php ]; then
  mkdir -p /var/www/html

  wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
  chmod +x wp-cli.phar
  mv wp-cli.phar /usr/local/bin/wp
  wp cli update --yes --allow-root
  wp core download --allow-root
  wp config create --dbname=$MYSQL_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost=mariadb --allow-root
  wp config set WP_REDIS_HOST redis --raw --allow-root
  wp config set WP_REDIS_PORT 6379 --raw --allow-root
  wp config set WP_REDIS_PASSWORD $REDIS_PASSWORD --raw --allow-root
  wp config set WP_REDIS_DATABASE 0 --raw --allow-root
  wp core install --url=https://junkpark.42.fr --title="JunkPark" --admin_user=$WP_USER --admin_password=$WP_PASSWORD --admin_email=$WP_EMAIL --skip-email --allow-root
  wp plugin install redis-cache --activate --allow-root
  wp redis enable --allow-root
  chown -R www-data:www-data /var/www/html
fi

exec "php-fpm7.3" "-F"
