#include <unistd.h>

void ft_putnbr(long nbr) {
	char symbol;

	if (nbr < 0)
		nbr *= -1;
	if (nbr / 10)
		ft_putnbr(nbr / 10);
	symbol = '0' + nbr % 10;
	write (1, &symbol, 1);
}
