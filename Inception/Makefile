COMPOSE=docker compose -f srcs/docker-compose.yml
BUILD=$(COMPOSE) build --parallel --no-cache
UP=$(COMPOSE) up -d
DOWN=$(COMPOSE) down
RESTART=$(COMPOSE) down && $(COMPOSE) up -d

.PHONY: all
all: build up

.PHONY: build
build:
	$(BUILD)

.PHONY: up
up:
	$(UP)

.PHONY: down
down:
	$(DOWN)

.PHONY: restart
restart:
	$(RESTART)

.PHONY: clean
clean:
	$(DOWN) --volumes

.PHONY: logs
logs:
	$(COMPOSE) logs -f
