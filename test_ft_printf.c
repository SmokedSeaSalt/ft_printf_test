#include <stddef.h> //to use NULL
#include <stdio.h> //to use printf
#include <fcntl.h> //to use open
#include <sys/stat.h> //to use open flags
#include <unistd.h> //to use close, read
#include <string.h> //to use strcmp
#include <stdlib.h> //to use malloc, free
#include "ft_printf.h" //to use ft_printf
#include "test.h"


void test_basics();
void test_c();
void test_s();
void test_d();
void test_i();
void test_u();
void test_pct();

int main(void)
{
	test_basics();
	test_c();
	test_s();
//	test_p();
	test_d();
	test_i();
	test_u();
//	test_x();
//	test_X();
	test_pct();

	//test_multiple args();


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
	test_1args("0 = %i", arg1, testcount++);
	arg1.argudigit = -0;
	test_1args("-1 = %i", arg1, testcount++);
	arg1.argudigit = 4294967295;
	test_1args("4294967295 = %i", arg1, testcount++);
	arg1.argudigit = 123;
	test_1args("123 = %i", arg1, testcount++);
	arg1.argudigit = -456;
	test_1args("-456 = %i", arg1, testcount++);
	arg1.argudigit = 1;
	test_1args("1 = %i", arg1, testcount++);
	arg1.argudigit = 10;
	test_1args("10 = %i", arg1, testcount++);

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


/*
	//if %p is NULL
	ret = printf("%p", (char *)NULL);
	printf(" | ret = %d\n", ret);
*/

