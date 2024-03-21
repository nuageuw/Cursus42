FROM debian:buster

# Install MariaDB client
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y mariadb-server moreutils gettext && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /run/mysqld
RUN chown -R mysql:mysql /run/mysqld

# Set up entrypoint
COPY tools/entrypoint.sh /
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]