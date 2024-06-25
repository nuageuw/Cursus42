## How to use 

1. Install pipenv: `pip install pipenv`
2. Install dependencies on your computer: `pipenv install`
3. Then build and up `docker compose build` `docker compose up -d` (if you want the logs `docker compose logs -f`)

After that your a good to go, the docker compose file use runserver so it's hot-realoading once you change python file
To have your js file and css file reloading proprely in your web browser you can do CTRL or CMD + F5 to deep reload the page and avoid the cache.

## Comment ca marche ?

ATTENTION: Avec NGINX, l'url de developpement est: https://localhost:8443/ et non pas le localhost:8000 de base (celui-ci étant dédier au backend soit django)

Avec l'ajout de NGINX le fonctionnement reste le meme seulement il est encore plus simple !

NGINX s'occupe de la partie front et donc de la partie SPA, il s'occupe d'automatiquement faire les redirections des codes HTML lors de l'appel de l'url. 

Tout passe par `router.js` dans la liste constante 'routes' il faudrait y mettre chaque URL lors de l'ajout d'une "page".

Pour plus de clareté, chaque 'page' devra avoir son propre fichier .html dans le dossier /front/templates. Il n'y pas besoin d'utiliser de base .html car le code se systématiquement réencoder dans l'index.html. Aussi dans les fichiers html des pages il n'y aura pas besoin de redéfinir le body, simplement faire `<div class="nom_de_la_page"></div>` puis d'y ajouter le code de la page dans cette div, dans de rare cas nous auront peut-etre besoin d'overwrite le code de l'index mais on verra plus tard.

Meme chose pour les fichiers js et css dédié à certaine page. Exemple si on crée la page `profile.html` elle aura dans le dossier CSS un `profile.css` et un `profile.js` dans le dossier JS

Django ne s'occupe pas du front, cela signifie qu'il ne gere ni les templates, ni les views, ni les urls, ... Il sera exclusivement utilisé comme API. C'est à dire qu'il sera notre accès à la base de données, dans le fichier `views.py` toutes les fonctions serviront à envoyer au lire des données dans la DB. Celles-ci nous seront renvoyées au format JSON, que nous pourront ensuite décoder et interpreter sans probleme avec notre JavaScript.

C'est tout ceci qui fait de notre Transcendance un SPA correct et nous n'auront plus besoin d'y chipoter.

## Ce qu'il reste a faire au niveau setup

- Configurer NGINX pour le WS et WSS (ce sera fait lorsque nous coderont le chat et autres demandant des websocket)

- Configurer django en SSL (ce sera fait lorsque nous auront quasiement finis le projet)
