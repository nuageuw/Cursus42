FROM debian:buster

RUN apt update -y
RUN apt upgrade -y
RUN apt-get install mariadb-server -y

COPY conf/50-server.cnf	/etc/mysql/mariadb.conf.d/50-server.cnf

COPY tools/config.sh /usr/local/bin/config.sh
RUN chmod +x /usr/local/bin/config.sh
CMD ["/usr/local/bin/config.sh"]