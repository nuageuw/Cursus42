# Use Debian Buster as the base image
FROM debian:buster

# Install PHP-FPM and other dependencies
RUN apt-get update && \
    apt-get install -y php-fpm php-mysql net-tools mariadb-client gettext moreutils curl && \
    rm -rf /var/lib/apt/lists/*

# Install WP-CLI
RUN curl -o /usr/local/bin/wp https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x /usr/local/bin/wp

# Create directory for PHP-FPM socket
RUN mkdir -p /run/php && chown www-data:www-data /run/php

# Create directory for WordPress installation and set permissions
RUN mkdir -p /var/www/html && chown www-data:www-data /var/www/html

# Expose port for PHP-FPM
EXPOSE 9000

# Copy the initialization script and entrypoint script
COPY tools/wordpress_init.sh /
COPY tools/wordpress.sh /

# Make scripts executable
RUN chmod +x /wordpress_init.sh /wordpress.sh

# Start WordPress initialization script as entrypoint
ENTRYPOINT ["/wordpress.sh"]
