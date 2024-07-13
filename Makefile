
in: # into docker container
	docker-compose up -d
	docker-compose exec working bash

down: # down docker container
	docker-compose down

cp:
	docker-compose up -d
	make rm
	docker-compose cp ./submit/. working:/app
	docker-compose exec -u root -T  working  chown -R pipex /app

rm:
	docker-compose up -d
	docker-compose exec -u root working bash -c 'test -d /app && rm -rf /app/*; exit 0'

test:
	docker-compose up -d
	make cp
	docker-compose exec -Tw /app working  make test
