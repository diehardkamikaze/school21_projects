server:
	gcc -Wall -Wextra -Werror server.c utils.c -I. -o server

client:
	gcc -Wall -Wextra -Werror client.c -I. -o client

clear:
	rm client
	rm server

re: clear server


# ./client 960 "$(< tests/1000)"""
