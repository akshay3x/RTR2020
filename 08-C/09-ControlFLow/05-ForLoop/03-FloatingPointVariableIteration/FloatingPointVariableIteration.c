#include <stdio.h>

int main(void)
{
	//variable declarations
	float ac_f;
	float ac_f_num = 0.90111; //simply change this value ONLY to get different outputs...

	//code
	printf("\n");
	printf("Printing %f to %f :\n\n", ac_f_num, (ac_f_num * 10.000000f));
	
	for (ac_f = ac_f_num; ac_f <= (ac_f_num * 10.0f); ac_f = ac_f + ac_f_num)
	{
		printf("\t %f \n", ac_f);
	}

	printf("\n");

	return (0);
}
