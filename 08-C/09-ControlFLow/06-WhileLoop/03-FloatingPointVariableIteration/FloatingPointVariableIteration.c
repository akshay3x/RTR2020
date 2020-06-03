#include <stdio.h>

int main(void)
{
	//variable declarations
	float ac_f;
	float ac_f_num = 2.3f; 
	
	//code
	printf("Printing %f to %f :\n\n", ac_f_num, (ac_f_num * 10.0f));

	ac_f = ac_f_num;

	while(ac_f <= (ac_f_num * 10.0f))
	{
		printf("\t %f \n", ac_f);
		ac_f = ac_f + ac_f_num;
	}

	printf("\n");

	return (0);
}
