#include "ft_printf.h"

int main(void)
{
	long int n;
	ft_printf("egererge %200s%ln", "ger", &n);
	ft_printf("\n%d\n", n);
	return (0);
}
