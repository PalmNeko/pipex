
IS_UP_CMD = false

up: # up container
	test "$(IS_UP_CMD)" = "false" && docker-compose up -d
	$(eval IS_UP_CMD = true)

in: up # into docker container
	docker-compose exec working bash

down: # down docker container
	docker-compose down

stat: # show stat
	docker-compose stats --no-stream

cp: up rm # copy submit files
	docker-compose cp ./submit/. working:/app
	docker-compose exec -u root -T  working  chown -R pipex /app

rm: up # rm submit files
	docker-compose exec -u root working bash -c 'test -d /app && rm -rf /app/*; exit 0'

test: cp # test submit files
	docker-compose exec -Tw /app working  make test

help: # show this help
	@cat Makefile \
		| grep -E '^[[:print:]].*:.*#' \
		| sed -e 's/ .*#//g' \
		| awk -F ":" '{printf "%5s %s\n",$$1,$$2}'
