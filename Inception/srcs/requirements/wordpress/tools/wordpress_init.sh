#!/bin/bash
sleep 10

if [ ! -f "/var/www/html/wp-config.php" ]; then
    wp core download --path=/var/www/html --allow-root

    wp config create --allow-root \
        --dbhost=$MARIADB_HOST \
        --dbname=$MARIADB_NAME \
        --dbuser=$MARIADB_USER \
        --dbpass=$MARIADB_PASSWORD \
        --path='/var/www/html'

    wp core install \
        --path=/var/www/html \
        --url=$WORDPRESS_URL \
        --title=$WORDPRESS_TITLE \
        --admin_user=$WORDPRESS_ROOT_USER \
        --admin_password=$WORDPRESS_ROOT_PASSWORD \
        --admin_email=$WORDPRESS_ROOT_EMAIL

    wp user create \
        $WORDPRESS_USER $WORDPRESS_USER_EMAIL \
        --user_pass=$WORDPRESS_USER_PASSWORD \
        --role=author --path=/var/www/html
fi
