#include <unistd.h>
#include <signal.h>

void ft_putnbr(int nbr);

void main_signal_handler(int signal) {
	if (signal == SIGUSR1)
		write(1,"0", 1);
	if (signal == SIGUSR2)
		write(1,"1", 1);
}

int override_signal_behavior() {
	struct sigaction sig_catcher;

	sig_catcher.sa_handler = main_signal_handler;
	sig_catcher.sa_flags = SA_NODEFER | SA_RESTART;
//	sig_catcher.sa_flags = 0;
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
