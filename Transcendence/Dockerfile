FROM python:3.10-slim

RUN apt-get update && apt-get install -y \
    libpq-dev \
    gcc \
    netcat-openbsd \ 
    dumb-init openssl \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY Pipfile Pipfile.lock /app/
RUN pip install pipenv && pipenv install --system

COPY . /app/

COPY entrypoint.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/entrypoint.sh

RUN mkdir -p /etc/ssl/certs
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/certs/localhost.key -out /etc/ssl/certs/localhost.crt -subj "/C=BE/ST=W/L=W/O=42/OU=42/CN=localhost"

EXPOSE 443

ENTRYPOINT ["entrypoint.sh"]