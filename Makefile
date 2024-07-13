
in: # into docker container
	docker-compose up -d
	docker-compose exec working bash

down: # down docker container
	docker-compose down

test:
	docker-compose up -d
	docker-compose cp ./submit working:/app
	docker-compose exec -Tw /app working  make test
