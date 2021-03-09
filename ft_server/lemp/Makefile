# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/09 12:30:38 by mchau             #+#    #+#              #
#    Updated: 2021/03/09 17:44:46 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: build run

build:
	docker build -t school21 .

run:
	docker run -it -p 80:80 -p 443:443 --name sch21 school21
#	docker exec -it sch21 bash
stop:
	docker stop sch21

clean:
	docker rm sch21 | true
	docker rmi school21
