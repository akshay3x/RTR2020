#include <stdio.h>

int ac_global_count = 0;

int main(void)
{
	//function prototypes
	void ac_change_count(void);
	void ac_change_count_one(void); //function defined in File_01.c
	void ac_change_count_two(void); //function defined in File_02.c

	//code
	printf("\n");

	ac_change_count();
	ac_change_count_one(); //function defined in File_01.c
	ac_change_count_two(); //function defined in File_02.c

	return(0);
}

void ac_change_count(void)
{
	//code
	ac_global_count = ac_global_count + 5;
	printf("Global Count value = %d\n", ac_global_count);

}
