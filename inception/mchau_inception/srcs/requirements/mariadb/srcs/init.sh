# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    init.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/09 12:10:52 by mchau             #+#    #+#              #
#    Updated: 2021/07/24 18:33:23 by mchau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#todo проверить чтобы не пускало без пароля в mysql и выкинуть рут ?

#!/bin/bash
service mysql start
# Configure a wordpress database using pipe and mysql command
echo "source /mchau.sql;" | mysql -u root --skip-password
#echo "update user set password=PASSWORD("almaz") where User='root';" | mysql -u root --skip-password
#echo "flush privileges;" | mysql -u root --skip-password
#echo "fupdate user set plugin='' where User='root';" | mysql -u root --skip-password
#echo "CREATE USER 'root'@'%' IDENTIFIED BY 'almaz'; GRANT ALL ON *.* TO 'root'@'%' WITH GRANT OPTION; FLUSH PRIVILEGES;" | mysql -u root --skip-password
echo "CREATE USER 'mchau'@'%' IDENTIFIED BY 'mchau'; GRANT ALL ON *.* TO 'mchau'@'%' WITH GRANT OPTION; FLUSH PRIVILEGES;" | mysql -u root --skip-password
echo "GRANT ALL PRIVILEGES ON mchau.* TO 'root'@'localhost' WITH GRANT OPTION;" | mysql -u root --skip-password
echo "FLUSH PRIVILEGES;" | mysql -u root --skip-password
echo "SET PASSWORD FOR root@'%'=PASSWORD('almaz');"| mysql -u root --skip-password
echo "update mysql.user set authentication_string=PASSWORD('almaz'), plugin='mysql_native_password' where user='root';"| mysql -u root --skip-password
mysql -e "alter user 'root'@'localhost' identified by 'almaz'";
# echo "update mysql.user set plugin='' where user='root';" | mysql -u root --skip-password
# nginx -g "daemon off;"
