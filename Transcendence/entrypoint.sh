#!/bin/bash

echo "Attente de la base de données..."
while ! nc -z db 5432; do
  sleep 0.1
done
echo "Base de données prête !"

echo "Application des migrations Django..."
cd myproject
python manage.py makemigrations --noinput
python manage.py migrate --noinput

# Collecter les fichiers statiques
echo "Collecte des fichiers statiques..."
python manage.py collectstatic --noinput


echo "Démarrage du serveur Django..."
daphne -e ssl:443:privateKey=/etc/ssl/certs/localhost.crt:certKey=/etc/ssl/certs/localhost.key -b 0.0.0.0 -p 8001 myproject.asgi:application & gunicorn --reload myproject.wsgi:application --bind 0.0.0.0:8000 --certfile "/etc/ssl/certs/localhost.crt" --keyfile "/etc/ssl/certs/localhost.key" --workers 4 --timeout 300