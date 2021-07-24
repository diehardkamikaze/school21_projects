# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    init.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/09 12:10:52 by mchau             #+#    #+#              #
#    Updated: 2021/03/09 17:44:21 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash
service mysql start
# Configure a wordpress database using pipe and musql command
echo "CREATE DATABASE mchau;" | mysql -u root --skip-password
echo "GRANT ALL PRIVILEGES ON mchau.* TO 'root'@'localhost' WITH GRANT OPTION;" | mysql -u root --skip-password
echo "FLUSH PRIVILEGES;" | mysql -u root --skip-password
echo "update mysql.user set plugin='' where user='root';" | mysql -u root --skip-password
service php7.3-fpm start
# nginx -g "daemon off;"

