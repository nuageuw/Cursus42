FROM debian:bullseye

RUN apt update -y
RUN apt upgrade -y
RUN apt install wget -y

RUN apt-get install -y php \
                    php php-fpm\
	                php-fpm \
	                php-mysql \
                    mariadb-server\
	                mariadb-client \
                    && rm -rf /var/lib/apt/lists/*

RUN mkdir /app
WORKDIR /app
RUN groupadd wordpress && useradd -g wordpress wordpress

RUN wget https://github.com/wp-cli/wp-cli/releases/download/v2.8.1/wp-cli-2.8.1.phar \
  && mv wp-cli-2.8.1.phar wp-cli.phar \
  && chmod +x wp-cli.phar \
  && mv wp-cli.phar /bin/wp

RUN wget https://wordpress.org/wordpress-6.2.2.tar.gz \
  && tar -zxvf wordpress-6.2.2.tar.gz \
  && mv wordpress/* . \
  && rm -rf wordpress wordpress-6.2.2.tar.gz \
  && chown -R wordpress:wordpress /app \
  && chmod -R 755 /app
EXPOSE 9000
COPY conf/entrypoint.sh /
RUN chmod +x /entrypoint.sh
USER wordpress:wordpress
# CMD ["/usr/sbin/php-fpm7.3", "-F"]
ENTRYPOINT ["/entrypoint.sh"]