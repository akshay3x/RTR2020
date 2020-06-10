#include <stdio.h>

int main(void)
{
	//function prototypes
	void ac_change_count(void);

	//variable declarations
	extern int ac_global_count;

	//code
	printf("\n");
	printf("Before change_count() call, Value = %d\n\n", ac_global_count);

	ac_change_count();

	printf("After change_count() call, value= %d\n", ac_global_count);
	printf("\n");

	return(0);

}

int ac_global_count = 0;

void ac_change_count(void)
{
	//code
	ac_global_count = 5;
	printf("In change_count(), value = %d\n\n", ac_global_count);

}

