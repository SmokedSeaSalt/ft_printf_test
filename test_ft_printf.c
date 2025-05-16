#include <stddef.h> //to use NULL
#include <stdio.h> //to use printf
#include <fcntl.h> //to use open
#include <sys/stat.h> //to use open flags
#include <unistd.h> //to use close, read
#include <string.h> //to use strcmp
#include <stdlib.h> //to use malloc, free
#include "ft_printf.h" //to use ft_printf
#include "test.h"


int main(void)
{
	test_basics();
	test_c();
	test_s();
	test_p();
	test_d();
	test_i();
	test_u();
	test_lx();
	test_ux();
	test_pct();
	test_multipleargs();
}

void test_8args(const char *str, union argUnion arg1, union argUnion arg2, union argUnion arg3,
	union argUnion arg4, union argUnion arg5, union argUnion arg6, union argUnion arg7,
	union argUnion arg8, int test_count)
{
	int exp_file = open("exp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	int res_file = open("res.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);

	//save default stdout
	int default_stdout = dup(STDOUT_FILENO);

	int ret_length;

	//redirect from stdout to exp.txt
	dup2(exp_file, STDOUT_FILENO);
	ret_length = printf(str, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	printf(" | ret = %d\n", ret_length);
	fflush(stdout);

	//redirect from exp.txt to res.txt
	dup2(res_file, STDOUT_FILENO);
	ret_length = ft_printf(str, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	printf(" | ret = %d\n", ret_length);
	fflush(stdout);

	//restore default stdout
	dup2(default_stdout, STDOUT_FILENO);

	//compare results
	lseek(exp_file, 0, SEEK_SET);
	lseek(res_file, 0, SEEK_SET);

	//create buffer to read files
	char *buffer_exp, *buffer_res;
	buffer_exp = calloc(1024, sizeof(char));
	buffer_res = calloc(1024, sizeof(char));

	if (buffer_exp == NULL || buffer_res == NULL)
		exit(-1);

	int exp_len = read(exp_file, buffer_exp, 1024);
	int res_len = read(res_file, buffer_res, 1024);

	if(exp_len == res_len && strcmp(buffer_exp, buffer_res) == 0)
	{
		printf("%s%d:OK %s", KGRN, test_count, KNRM);
		fflush(stdout);
	}
	else
	{
		printf("%s%d:KO\n%s", KRED, test_count, KNRM);
		printf("exp:%s != res:%s\n", buffer_exp, buffer_res);
		fflush(stdout);
	}

	close(exp_file);
	close(res_file);

	free(buffer_exp);
	free(buffer_res);
}

void test_1args(const char *str, union argUnion arg1, int test_count)
{
	int exp_file = open("exp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	int res_file = open("res.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);

	//save default stdout
	int default_stdout = dup(STDOUT_FILENO);

	int ret_length;

	union argUnion arg1union;

	//redirect from stdout to exp.txt
	dup2(exp_file, STDOUT_FILENO);
	ret_length = printf(str, arg1);
	printf(" | ret = %d\n", ret_length);
	fflush(stdout);

	//redirect from exp.txt to res.txt
	dup2(res_file, STDOUT_FILENO);
	ret_length = ft_printf(str, arg1);
	printf(" | ret = %d\n", ret_length);
	fflush(stdout);

	//restore default stdout
	dup2(default_stdout, STDOUT_FILENO);

	//compare results
	lseek(exp_file, 0, SEEK_SET);
	lseek(res_file, 0, SEEK_SET);

	//create buffer to read files
	char *buffer_exp, *buffer_res;
	buffer_exp = calloc(1024, sizeof(char));
	buffer_res = calloc(1024, sizeof(char));

	if (buffer_exp == NULL || buffer_res == NULL)
		exit(-1);

	int exp_len = read(exp_file, buffer_exp, 1024);
	int res_len = read(res_file, buffer_res, 1024);

	if(exp_len == res_len && strcmp(buffer_exp, buffer_res) == 0)
	{
		printf("%s%d:OK %s", KGRN, test_count, KNRM);
		fflush(stdout);
	}
	else
	{
		printf("%s%d:KO\n%s", KRED, test_count, KNRM);
		printf("exp:%s != res:%s\n", buffer_exp, buffer_res);
		fflush(stdout);
	}

	close(exp_file);
	close(res_file);

	free(buffer_exp);
	free(buffer_res);
}




void test_0args(const char *str, int test_count)
{
	int exp_file = open("exp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	int res_file = open("res.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);

	//save default stdout
	int default_stdout = dup(STDOUT_FILENO);

	int ret_length;

	//redirect from stdout to exp.txt
	dup2(exp_file, STDOUT_FILENO);
	ret_length = printf(str);
	printf(" | ret = %d\n", ret_length);
	fflush(stdout);

	//redirect from exp.txt to res.txt
	dup2(res_file, STDOUT_FILENO);
	ret_length = ft_printf(str);
	printf(" | ret = %d\n", ret_length);
	fflush(stdout);

	//restore default stdout
	dup2(default_stdout, STDOUT_FILENO);

	//compare results
	lseek(exp_file, 0, SEEK_SET);
	lseek(res_file, 0, SEEK_SET);

	//create buffer to read files
	char *buffer_exp, *buffer_res;
	buffer_exp = calloc(1024, sizeof(char));
	buffer_res = calloc(1024, sizeof(char));

	if (buffer_exp == NULL || buffer_res == NULL)
		exit(-1);

	int exp_len = read(exp_file, buffer_exp, 1024);
	int res_len = read(res_file, buffer_res, 1024);

	if(exp_len == res_len && strcmp(buffer_exp, buffer_res) == 0)
	{
		printf("%s%d:OK %s", KGRN, test_count, KNRM);
		fflush(stdout);
	}
	else
	{
		printf("%s%d:KO\n%s", KRED, test_count, KNRM);
		printf("exp:%s != res:%s\n", buffer_exp, buffer_res);
		fflush(stdout);
	}

	close(exp_file);
	close(res_file);

	free(buffer_exp);
	free(buffer_res);
}




void test_basics()
{

	int testcount = 1;
	printf("Basic tests:\n");

	test_0args("test", testcount++);
	test_0args("\n\t    some whitespaces", testcount++);
	test_0args((char*)NULL, testcount++);
	test_0args("", testcount++);
	//test_0args("%%", testcount++);

	printf("\n");
}

void test_c()
{
	int testcount = 1;
	//enum argtype arg1type = CHAR;
	union argUnion arg1;


	printf("Char tests:\n");

	arg1.argchar = 'x';
	test_1args("x = %c", arg1, testcount++);
	arg1.argchar = (char)200;
	test_1args("above 128 = %c", arg1, testcount++);

	printf("\n");
}

void test_s()
{
	int testcount = 1;
	//enum argtype arg1type = CHAR;
	union argUnion arg1;

	printf("string tests:\n");

	arg1.argstring = "this is a string";
	test_1args("x = %s", arg1, testcount++);
	arg1.argstring = (char *)NULL;
	test_1args("above 128 = %s", arg1, testcount++);

	printf("\n");
}

void test_d()
{
	int testcount = 1;

	union argUnion arg1;

	printf("digit tests:\n");

	arg1.argddigit = 0;
	test_1args("0 = %d", arg1, testcount++);
	arg1.argddigit = -0;
	test_1args("-1 = %d", arg1, testcount++);
	arg1.argddigit = 2147483647;
	test_1args("2147483647 = %d", arg1, testcount++);
	arg1.argddigit = -2147483648;
	test_1args("-2147483648 = %d", arg1, testcount++);
	arg1.argddigit = 123;
	test_1args("123 = %d", arg1, testcount++);
	arg1.argddigit = -456;
	test_1args("-456 = %d", arg1, testcount++);
	arg1.argddigit = 1;
	test_1args("1 = %d", arg1, testcount++);
	arg1.argddigit = 10;
	test_1args("10 = %d", arg1, testcount++);

	printf("\n");
}

void test_i()
{
	int testcount = 1;

	union argUnion arg1;

	printf("int tests:\n");

	arg1.argidigit = 0;
	test_1args("0 = %i", arg1, testcount++);
	arg1.argidigit = -0;
	test_1args("-1 = %i", arg1, testcount++);
	arg1.argidigit = 2147483647;
	test_1args("2147483647 = %i", arg1, testcount++);
	arg1.argidigit = -2147483648;
	test_1args("-2147483648 = %i", arg1, testcount++);
	arg1.argidigit = 123;
	test_1args("123 = %i", arg1, testcount++);
	arg1.argidigit = -456;
	test_1args("-456 = %i", arg1, testcount++);
	arg1.argidigit = 1;
	test_1args("1 = %i", arg1, testcount++);
	arg1.argidigit = 10;
	test_1args("10 = %i", arg1, testcount++);

	printf("\n");
}

void test_u()
{
	int testcount = 1;

	union argUnion arg1;

	printf("unsigned int tests:\n");

	arg1.argudigit = 0;
	test_1args("0 = %u", arg1, testcount++);
	arg1.argudigit = -0;
	test_1args("-1 = %u", arg1, testcount++);
	arg1.argudigit = 4294967295;
	test_1args("4294967295 = %u", arg1, testcount++);
	arg1.argudigit = 123;
	test_1args("123 = %u", arg1, testcount++);
	arg1.argudigit = -456;
	test_1args("-456 = %u", arg1, testcount++);
	arg1.argudigit = 1;
	test_1args("1 = %u", arg1, testcount++);
	arg1.argudigit = 10;
	test_1args("10 = %u", arg1, testcount++);

	printf("\n");
}

void test_lx()
{
	int testcount = 1;

	union argUnion arg1;

	printf("lowercase hex tests:\n");

	arg1.arglhex = 0;
	test_1args("0 = %x", arg1, testcount++);
	arg1.arglhex = -0;
	test_1args("-1 = %x", arg1, testcount++);
	arg1.arglhex = 4294967295;
	test_1args("4294967295 = %x", arg1, testcount++);
	arg1.arglhex = 123;
	test_1args("123 = %x", arg1, testcount++);
	arg1.arglhex = -456;
	test_1args("-456 = %x", arg1, testcount++);
	arg1.arglhex = 1;
	test_1args("1 = %x", arg1, testcount++);
	arg1.arglhex = 10;
	test_1args("10 = %x", arg1, testcount++);

	printf("\n");
}

void test_ux()
{
	int testcount = 1;

	union argUnion arg1;

	printf("uppercase hex tests:\n");

	arg1.arguhex = 0;
	test_1args("0 = %X", arg1, testcount++);
	arg1.arguhex = -0;
	test_1args("-1 = %X", arg1, testcount++);
	arg1.arguhex = 4294967295;
	test_1args("4294967295 = %X", arg1, testcount++);
	arg1.arguhex = 123;
	test_1args("123 = %X", arg1, testcount++);
	arg1.arguhex = -456;
	test_1args("-456 = %X", arg1, testcount++);
	arg1.arguhex = 1;
	test_1args("1 = %X", arg1, testcount++);
	arg1.arguhex = 10;
	test_1args("10 = %X", arg1, testcount++);

	printf("\n");
}

void test_p()
{
	int testcount = 1;

	union argUnion arg1;

	printf("pointer adress tests:\n");

	arg1.argpointer = "test";
	test_1args("%p", arg1, testcount++);
	arg1.argpointer = NULL;
	test_1args("%p", arg1, testcount++);
	arg1.argpointer = &testcount;
	test_1args("%p", arg1, testcount++);

	printf("\n");
}

void test_pct()
{
	int testcount = 1;

	union argUnion arg1;

	printf("percentage %% tests:\n");

	test_0args("%%", testcount++);
	test_0args("%%%% %%", testcount++);
	arg1.argddigit = 42;
	test_1args("this is %d%%", arg1, testcount++);

	printf("\n");
}

void test_multipleargs()
{

	int testcount = 1;

	printf("8 arguments tests:\n");

	union argUnion arg1;
	arg1.argchar = 'X';
	union argUnion arg2;
	arg2.argddigit = 42;
	union argUnion arg3;
	arg3.argidigit = -42;
	union argUnion arg4;
	arg4.arglhex = 345;
	union argUnion arg5;
	arg5.argpointer = &arg4;
	union argUnion arg6;
	arg6.argstring = "teststring";
	union argUnion arg7;
	arg7.argudigit = 234235;
	union argUnion arg8;
	arg8.arguhex = 2875;
	test_8args("%c%d%i%x%p%s%u%X", arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, testcount);

	printf("\n");
}
