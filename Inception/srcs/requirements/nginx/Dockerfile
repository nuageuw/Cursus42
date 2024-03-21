FROM debian:buster

# Install NGINX and SSL certificates
RUN apt-get update && \
    apt-get install -y nginx openssl && \
    rm -rf /var/lib/apt/lists/*

# Create directory for SSL certificates
RUN mkdir -p /etc/nginx/ssl

# Generate SSL certificates
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/aburnott.key \
    -out /etc/nginx/ssl/aburnott.crt \
    -subj "/CN=aburnott"

# Copy NGINX configuration
RUN mkdir -p /run/nginx
COPY conf/nginx.conf /etc/nginx/nginx.conf

# Expose ports
EXPOSE 443

# Start NGINX
CMD ["nginx", "-g", "daemon off;"]