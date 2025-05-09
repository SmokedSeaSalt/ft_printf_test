#include <stddef.h> //to use NULL
#include <stdio.h> //to use printf
#include "ft_printf.h" //to use ft_printf

int main(void)
{
	int ret;

	//basic input
	ret = ft_printf("test");
	printf(" | ret = %d\n", ret);
	fflush(stdout);

	//if input string is NULL
	ret = ft_printf((char *)NULL);
	printf(" | ret = %d\n", ret);
	fflush(stdout);

	//if input is valid but empty
	ret = ft_printf("");
	printf(" | ret = %d\n", ret);
	fflush(stdout);
/*
	//if %s is NULL
	ret = ft_printf("%s", (char *)NULL);
	printf(" | ret = %d\n", ret);

	//if %p is NULL
	ret = printf("%p", (char *)NULL);
	printf(" | ret = %d\n", ret);
*/
}
