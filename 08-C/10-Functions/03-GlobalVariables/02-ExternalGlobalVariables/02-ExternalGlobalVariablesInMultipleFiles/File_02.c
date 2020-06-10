#include<stdio.h>



void ac_change_count_two(void)
{
	//code
	extern int ac_global_count;
	
	ac_global_count = ac_global_count + 1;
	printf("global_count_two(): value = %d in file_02.c \n", ac_global_count);

}
