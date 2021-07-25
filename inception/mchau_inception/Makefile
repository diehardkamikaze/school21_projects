
all:
	docker-compose -f ./srcs/docker-compose.yml up --build -d

stop:
	docker stop nginx mariadb wordpress
	docker rm nginx mariadb wordpress
	#docker-compose -f ./srcs/docker-compose.yml down

clean: stop
	rm -rf /Users/mchau/data/wp_vol/*
	rm -rf /Users/mchau/data/db_vol/*

re: clean
	docker-compose -f ./srcs/docker-compose.yml up --build -d

# mysql -u root -p
# show databases;
# use mchau;
# show tables;
# select * from ... ;
# exit
