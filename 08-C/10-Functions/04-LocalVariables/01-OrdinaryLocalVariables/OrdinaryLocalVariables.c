#include <stdio.h>

int main(void)
{
	int ac_a = 5;

	//function prototypes
	void ac_change_count(void);

	//code
	printf("\n");
	printf("Local variable in main(): A = %d\n\n", ac_a);

	ac_change_count();

	ac_change_count();

	ac_change_count();

	return(0);

}

void ac_change_count(void)
{
	int ac_local_count = 0;

	//code
	ac_local_count = ac_local_count + 1;
	printf("Local variable in change_count() = %d\n", ac_local_count);

}
