#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void ft_putnbr(int nbr);

void ft_putstr(char *c);

void exit_with_error(char *error) {
	ft_putstr(error);
	exit(1);
}

void	work_is_ready(int client_pid, int sig) {
	if (kill(client_pid, sig)) // check it
		exit(0);
}

void main_signal_handler(int signal) {
	static int bit;
	static char symbol;

	if (signal == SIGUSR1)
		symbol &= (255 - (1 << bit));
	if (signal == SIGUSR2)
		symbol |= 1 << bit;
	bit++;
	if (bit == 8) {
		bit = 0;
		write(1, &symbol, 1);
	}
}

int override_signal_behavior() {
	struct sigaction sig_catcher;

	sig_catcher.sa_handler = main_signal_handler;
//	sig_catcher.sa_flags = SA_NODEFER | SA_RESTART;
	sig_catcher.sa_flags = 0;
	sigaction(SIGUSR1, &sig_catcher, 0);
	sigaction(SIGUSR2, &sig_catcher, 0);
	return (1);
}


int main() {
	int pid;

	pid = getpid();
	ft_putnbr(pid);
	write(1,"\n", 1);
	override_signal_behavior();

	while (1)
		pause();
	return (0);
}
