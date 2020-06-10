#include<stdio.h>

extern int ac_global_count;

void ac_change_count_one(void)
{
	//code
	ac_global_count = ac_global_count + 1;
	printf("global_count_one(): value = %d in file_01.c \n", ac_global_count);

}
