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

# installing telnet
RUN apt-get -y install telnet

#installing vim
RUN apt-get -y install vim


RUN apt-get -y install php7.3 php-mysql php-fpm php-xml
# установить php7.3
# php7.3 - интерпретатор версии 7.3
# php-mysql - устанавливает расширения(типа библиотеки) ext/mysql, ext/mysqli, и PDO_MYSQL.для Wordpress
# php-fpm - (Fastcgi process manage) программный пакет, работающий с веб-сервером(nginx, apache),
# сервак статические данные обрабатывает, а обработку скриптов направляет сюда
# php-pdo - опять скорее всего расширение для работы с бд
# php-gd - gd graphic library, библиотека для работы с изображениями
# php-cli - интерфейс командной строки php, он здесь нужен?
# php-mbstring - библиотека для работы с многобайтовыми строками, с unicode в основном
# php-xml - внезапно затребовал phpmyadmin, скорее всего просто библиотека для работы с xml

WORKDIR /var/www/html/

RUN rm -rf * | true
# очистить рабочую директорию


#WP installation and configure
RUN wget https://wordpress.org/latest.tar.gz
# загрузить последнюю версию WP

RUN tar -xvzf latest.tar.gz && rm -rf latest.tar.gz
# распаковать последнюю версию в текущую папку и удалить архив

RUN mv ./wordpress/* ./ && rm -rf wordpress
# вытащить все из WP в корневую директорию

COPY ./srcs/wp-config.php ./
# скопировать заготовленный конфиг WP из текущей папки в образ

#End WP installing

COPY ./srcs/init.sh ./
# скопировать из текущей директории файл в образ
# скопировать из текущей директории файл в образ

# php config update
COPY ./srcs/www.conf /etc/php/7.3/fpm/pool.d/

# fix error with php/run
RUN mkdir /run/php

RUN chmod +x init.sh
# CMD ./init.sh
RUN ./init.sh


ENTRYPOINT ["/usr/sbin/php-fpm7.3"]
CMD ["-F"]
# запустить во время запуска контейнера
