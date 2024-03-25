# FROM debian:buster

# RUN apt update -y
# RUN apt upgrade -y
# RUN apt install wget -y

# RUN apt-get install -y php7.3\
# 	                php-fpm\
# 	                php-mysql\
# 	                mariadb-client \
# 					sendmail

# RUN wget https://fr.wordpress.org/wordpress-6.0-fr_FR.tar.gz -P /var/www
# RUN cd /var/www && tar -xzf wordpress-6.0-fr_FR.tar.gz && rm wordpress-6.0-fr_FR.tar.gz

# RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
# RUN chmod +x wp-cli.phar
# RUN mv wp-cli.phar /usr/local/bin/wp
# # RUN chown -R root:root /var/www/var/www/html
# EXPOSE 9000
# COPY conf/entrypoint.sh /usr/local/bin/entrypoint.sh
# COPY conf/wp-config.php /var/www/html/wp-config.php
# RUN chmod +x /usr/local/bin/entrypoint.sh
# ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
# CMD ["/usr/sbin/php-fpm7.3", "-F"]

FROM debian:buster

RUN apt-get update && apt-get install -y php-fpm php-mysql curl net-tools mariadb-client && \
    mkdir /run/php && \
    sed -i 's/;cgi.fix_pathinfo=1/cgi.fix_pathinfo=0/g' /etc/php/7.3/fpm/php.ini && \
    sed -i 's/listen = \/run\/php\/php7.3-fpm.sock/listen = 9000/g' /etc/php/7.3/fpm/pool.d/www.conf && \
	rm -rf /var/lib/apt/lists/*

COPY /conf/entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

ENTRYPOINT [ "/entrypoint.sh" ]