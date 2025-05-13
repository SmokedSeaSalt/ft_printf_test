#ifndef TEST_H
# define TEST_H

#include "ft_printf.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void test_basics();
void test_c();
void test_s();
void test_p();
void test_d();
void test_i();
void test_u();
void test_lx();
void test_ux();
void test_pct();
void test_multipleargs();

union argUnion
{
	char argchar;
	char *argstring;
	void *argpointer;
	int argddigit;
	int argidigit;
	unsigned int argudigit;
	unsigned int arglhex;
	unsigned int arguhex;
};

#endif
