#!/bin/bash

# Perform variable substitution in the initialization script
envsubst < /wordpress_init.sh > /wordpress_init.sh

# Check if wp-config.php file exists; if not, initialize WordPress
if [ ! -f /var/www/html/wp-config.php ]; then
    /wordpress_init.sh
fi

# Start PHP-FPM in foreground mode
php-fpm7.3 -F
