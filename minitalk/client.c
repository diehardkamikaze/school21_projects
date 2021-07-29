#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_atoi(char *str) {
	int i;
	int sign;
	long result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || (str[i] == '-' && (sign = -1)))
		i++;
	while ('0' <= str[i]  && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}


void	time_expiration_handler(int sig) {
	sig++;
	write(1,"Time is over!\n", 14);
	exit(1);
}

#include <stdio.h> // del that
// dbawit obrabot4ik na SIGUSR1 i SIGUSR2 + exit po counter
void time_test(unsigned int time) {
	struct sigaction catcher;
	catcher.sa_handler = time_expiration_handler;
	sigemptyset(&catcher.sa_mask);
	sigaddset(&catcher.sa_mask, SIGUSR1);
	sigaddset(&catcher.sa_mask, SIGUSR2);
	sigaction(SIGALRM, &catcher, NULL);
	//	exit(1); // prokinut 4erez funct
	alarm(time);
}

int main(int argc, char **argv) {
	int pid;
	int i;
	int j;
	char c;
	int razn = SIGUSR2 - SIGUSR1;

	time_test(2);
	if (argc != 3)
		return (1);
	i = 0;
	if ((pid = ft_atoi(argv[1])) <= 0)
		return 1;

	while(argv[2][i] != 0)
	{
		j = 0;
		c = argv[2][i];
		while (j < 8)
		{
			kill(pid, 10 + razn * (c % 2));
			c /= 2;
			j++;
		usleep(100);
		}
		i++;
	}
	pause();
	return (1);
}
