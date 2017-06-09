#include <stdio.h>
#include <stdlib.h>


int ft_nblen(long n, int base)
{
    int len;

    if (base < 2)
        return (-1);

    len = (n < 0 && base == 10) ? 2 : 1;
    while (n /= base)
        len++;
        
    return (len);
}

int main(int argc, char **argv)
{	
	long n = atol(argv[1]);
	int base = atoi(argv[2]);
	
	printf("nblen(%ld) = %d\n", n, ft_nblen(n, base));	

	return (0);
}
