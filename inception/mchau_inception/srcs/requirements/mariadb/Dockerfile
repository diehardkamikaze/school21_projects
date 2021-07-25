# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/09 11:31:01 by mchau             #+#    #+#              #
#    Updated: 2021/03/09 17:31:13 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

From debian:buster
#начинаем с образа debian:buster

RUN apt-get update
# обновить индекс пакетов

RUN apt-get upgrade -y
# обновить все установленные пакеты

RUN apt-get -y install wget
# установить пакет wget

RUN apt-get -y install mariadb-server
# установить mariadb

# installing telnet
RUN apt-get -y install telnet

# installing VIM
RUN apt-get -y install vim

RUN apt-get -y install php7.3 php-mysql php-fpm php-xml

#change mariadb conf
COPY ./srcs/my.cnf /etc/mysql

COPY ./srcs/mchau.sql /mchau.sql

COPY ./srcs/init.sh ./
# скопировать из текущей директории файл в образ

RUN chmod +x init.sh
# CMD ./init.sh
RUN ./init.sh
ENTRYPOINT ["mysqld"]
CMD ["-u root"]
#CMD sleep 999999
# запустить во время запуска контейнера
