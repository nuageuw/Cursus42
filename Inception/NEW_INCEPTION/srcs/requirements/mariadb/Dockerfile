FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    mariadb-server \
  && rm -rf /var/lib/apt/lists/*

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/config.sh /
RUN chmod +x /config.sh

ENTRYPOINT ["bash", "config.sh"]