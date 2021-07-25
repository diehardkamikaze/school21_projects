
all:
	sudo docker-compose -f ./srcs/docker-compose.yml up --build -d

stop:
	sudo docker stop nginx mariadb wordpress
	sudo docker rm nginx mariadb wordpress
	#docker-compose -f ./srcs/docker-compose.yml down

clean: stop
	sudo rm -rf /home/mchau/data/wp_vol/*
	sudo rm -rf /home/mchau/data/db_vol/*

re: clean
	sudo docker-compose -f ./srcs/docker-compose.yml up --build -d

# mysql -u root -p
# show databases;
# use mchau;
# show tables;
# select * from ... ;
# exit
