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

# installing vim
RUN apt-get -y install vim

# package
RUN apt-get install -y procps

#nginx installation and configure
RUN apt-get -y install nginx
# установить nginx
COPY ./srcs/default /etc/nginx/sites-available/
# заменить дефолтный конфиг unix

WORKDIR /var/www/html/

# RUN rm -rf * | true
# очистить рабочую директорию

# #phpmyadmin installation and configure
# RUN wget https://files.phpmyadmin.net/phpMyAdmin/5.1.0/phpMyAdmin-5.1.0-english.tar.gz
# # скачать версию 5.1.0 phpmyadmin
#
# RUN tar -xf phpMyAdmin-5.1.0-english.tar.gz && rm -rf phpMyAdmin-5.1.0-english.tar.gz
# # распаковать в текущую директорию и удалить архив
#
# RUN mv phpMyAdmin-5.1.0-english phpmyadmin
# # переименовать папку
#
# COPY ./srcs/config.inc.php phpmyadmin
# # скопировать заготовленный конфиг phpmyadmin в соответствующую папку в образ

#End WP installing

#SSL settings
RUN openssl req -x509 -nodes -days 90 -subj "/C=RU/ST=Russia/L=Kazan/O=school21/OU=mchau//emailAddress=mchau@student.21-school.ru/CN=localhost" -newkey rsa:2048 -keyout /etc/ssl/mchau-selfsigned.key -out /etc/ssl/mchau-selfsigned.crt;
# https://stackoverflow.com/questions/10175812/how-to-create-a-self-signed-certificate-with-openssl
# openssl - open-source криптографическая библиотека на С, реализующая протоколы SSL и TLS
# Имеет инструменты для генерации приватных ключей RSA и CSR-запросов, управления сертификатами и код./декод.
# req - в первую очередь используется для создания CSR-запросов, кроме того - для создания самощаверяющих
# сертификатов
# параметр к req -x509 - генерировать самозаверяющий сертификат вместо CSR-запроса. Обычно используется
#   для тестового сертификата. Если нет параметра set_serial будет использовано большое случайное число.
# параметр к req -nodes: - при наличии этой опции приватные ключ не будет зашифрован при помощи passphrasei
# параметр к req -days: если задан x509, то назначает срок действия сертификата
# CRS-параметры (-subj):
#  - Country Name – ISO-кодстраны
#  - State or Province Name – область, где была проведена официальная регистрация компании
#  - Locality Name – город, где была проведена официальная регистрация компании
#  - Organization Name – полное название организации (без сокращений)
#  - Organizational Unit Name – название отдела организации
#  - Common Name – полное доменное имя сервера

# RUN chown -R www-data:www-data *
# # веб-сервер должен работать под определенным пользователем, поскольку если он будет
# # взломан, то у него не будет root прав для на сервере
# # так, nginx может работать только с теми файлами, к которым есть права у www-data
# #chown - change owner - заменить у всех файлов владельца и группа на www-data
# # -R - recursive
# # www-data:www-data - пользоваель:группа
# # * - на всех файлах
# # Это стандартный юзер nginx и php-fpm
#
# RUN chmod -R 755 /var/www/*
# # выдать права только на чтение всех файлов рекурсивно

# COPY ./srcs/init.sh ./
# скопировать из текущей директории файл в образ

# RUN chmod +x init.sh
# CMD ./init.sh
# RUN ./init.sh
ENTRYPOINT ["nginx"]
CMD ["-g",  "daemon off;"]
# запустить во время запуска контейнера
