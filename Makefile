
in: # into docker container
	docker-compose up -d
	docker-compose exec working bash

down: # down docker container
	docker-compose down

cp:
	docker-compose up -d
	docker-compose exec -u root -T  working  rm -rf /app/*
	docker-compose cp ./submit working:/app
	docker-compose exec -u root -T  working  chown -R pipex /app

test:
	docker-compose up -d
	docker-compose cp ./submit working:/app
	docker-compose exec -Tw /app working  make test
