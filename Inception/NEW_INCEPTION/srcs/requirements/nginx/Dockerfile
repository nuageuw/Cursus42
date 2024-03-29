FROM debian:bullseye

RUN apt update -y
RUN apt upgrade -y
RUN apt install -y nginx
RUN apt install vim -y
RUN apt install curl -y

RUN mkdir -p /etc/nginx/ssl

RUN apt-get install openssl -y

RUN openssl req -x509 -nodes -out /etc/nginx/ssl/aburnott.crt -keyout /etc/nginx/ssl/aburnott.key -subj "/C=FR/ST=IDF/L=Paris/O=42/OU=42/CN=aburnott.42.fr/UID=aburnott"

RUN mkdir -p /var/run/nginx

COPY conf/nginx.conf /etc/nginx/nginx.conf

RUN chmod 755 /var/www/html
RUN chown -R www-data:www-data /var/www/html

CMD [ "nginx", "-g", "daemon off;" ]