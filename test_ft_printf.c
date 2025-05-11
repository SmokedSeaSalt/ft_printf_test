#include <stddef.h> //to use NULL
#include <stdio.h> //to use printf
#include <fcntl.h> //to use open
#include <sys/stat.h> //to use open flags
#include <unistd.h> //to use close, read
#include "ft_printf.h" //to use ft_printf
#include "test.h" 

int main(void)
{


	//fill file fd with ft_printf tests 
	test_basics();
	test_c();
	test_s();
	test_p();
	test_di();
	test_u();
	test_x();
	test_X();
	test_pct();


	//fill file fd with printf tests



	//compare every scentence




}


test_0args(char *str, int test_count)
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
	close(STDOUT_FILENO);

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
		printf("%s%d:KO\n%s", KGRN, test_count, KNRM);
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
	printf("Basic tests:");
	fflush(stdout);

	test_0args("test", testcount++);
	test_0args((char*)NULL, testcount++);
	test_0args("", testcount++);
}
/*
	//if %s is NULL
	ret = ft_printf("%s", (char *)NULL);
	printf(" | ret = %d\n", ret);

	//if %p is NULL
	ret = printf("%p", (char *)NULL);
	printf(" | ret = %d\n", ret);
*/

