#include <stddef.h> //to use NULL
#include <stdio.h> //to use printf
#include "ft_printf.h" //to use ft_printf

int main(void)
{
	int ret;

	//if input string is NULL
	ret = printf((char *)NULL);
	printf(" | ret = %d\n", ret);

	ret = ft_printf((char *)NULL);
	printf(" | ret = %d\n", ret);

	//if input is valid but empty
	ret = printf("");
	printf(" | ret = %d\n", ret);

	ret = ft_printf("");
	printf(" | ret = %d\n", ret);



	ret = printf("%s", (char *)NULL);
	printf(" | ret = %d\n", ret);

	ret = printf("%p", (char *)NULL);
	printf(" | ret = %d\n", ret);
}
