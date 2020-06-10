#include <stdio.h>

int ac_global_count = 0;

int main(void)
{
	//function prototypes
	void ac_change_count_one(void);
	void ac_change_count_two(void);
	void ac_change_count_three(void);

	//code
	printf("\n");
	printf("main() : Value of global_count = %d\n", ac_global_count);

	ac_change_count_one();
	ac_change_count_two();
	ac_change_count_three();

	printf("\n");

	return(0);
}


void ac_change_count_one(void)
{

	//code
	ac_global_count = 202;
	printf("change_count_one() : Value of global_count = %d\n", ac_global_count);

}


void ac_change_count_two(void)
{
	//code
	ac_global_count = ac_global_count + 5;
	printf("change_count_two() : Value of global_count = %d\n", ac_global_count);

}

void ac_change_count_three(void)
{
	//code
	ac_global_count = ac_global_count + 203;
	printf("change_count_three() : Value of global_count = %d\n", ac_global_count);

}

