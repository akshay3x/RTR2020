#include <stdio.h>

int main(void)
{
	//variable declarations
	float ac_f;
	float ac_f_num = 0.339f;

	//code
	printf("\n");
	printf("Numbers %f to %f:\n\n", ac_f_num, (ac_f_num * 10.0f));

	ac_f = ac_f_num;
	
	do
	{
		printf("\t %f \n", ac_f);
		ac_f = ac_f + ac_f_num;

	} while (ac_f <= (ac_f_num * 10.0f));

	printf("\n");

	return (0);
}
