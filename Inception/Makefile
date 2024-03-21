# Define variables
COMPOSE=docker compose -f srcs/docker-compose.yml
BUILD=$(COMPOSE) build --parallel --no-cache
UP=$(COMPOSE) up -d
DOWN=$(COMPOSE) down
RESTART=$(COMPOSE) restart

# Default target
.PHONY: all
all: build up

# Build Docker containers
.PHONY: build
build:
	$(BUILD)

# Start Docker containers
.PHONY: up
up:
	$(UP)

# Stop Docker containers
.PHONY: down
down:
	$(DOWN)

# Restart Docker containers
.PHONY: restart
restart:
	$(RESTART)

# Clean up Docker volumes
.PHONY: clean
clean:
	$(DOWN) --volumes

# Show logs of Docker containers
.PHONY: logs
logs:
	$(COMPOSE) logs -f
