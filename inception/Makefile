NAME = inception

COMPOSE = docker compose -f srcs/docker-compose.yml
DATA_PATH = /home/vboxuser/data

all: $(NAME)

$(NAME):
	mkdir -p $(DATA_PATH)/mariadb $(DATA_PATH)/wordpress
	$(COMPOSE) up -d --build

clean:
	$(COMPOSE) down

fclean: clean
	docker system prune -af
	docker volume prune -f
	docker network prune -f

re: fclean all

.PHONY: all clean fclean re
