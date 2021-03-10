#include "ft_printf.h"
#include <stdio.h>


int	main(void)
{
	char str[] = "Bonjour Monde, c'est bien moi";

	ft_printf("Imprime moi ca mon loup : %50.8s\n", str);
	printf("Imprime moi ca mon loup : %50.8s\n", str);
	return (0);
}
