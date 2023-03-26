all: setup up

setup:
	@mkdir -p /home/junkpark/data/wordpress
	@mkdir -p /home/junkpark/data/mariadb
	@sudo echo "127.0.0.1 junkpark.42.fr" >> /etc/hosts
	@echo "Data directory created."

up: setup
	@docker-compose -f ./srcs/docker-compose.yml up -d --build
	@echo "Waiting for containers to start..."

down:
	@docker-compose -f ./srcs/docker-compose.yml down
	@echo "Containers stopped."

clean:
	@docker compose -f ./srcs/docker-compose.yml down --rmi all --volumes
	@echo "Containers stopped and images removed."

fclean: clean
	@sudo rm -rf /home/junkpark/data
	@sudo sed -i '/junkpark.42.fr/d' /etc/hosts
	@echo "Data removed."

re:
	make fclean
	make all

.PHONY: all setup up down clean fclean re
