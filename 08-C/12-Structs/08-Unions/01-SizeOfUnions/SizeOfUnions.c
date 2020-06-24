#include<stdio.h>

struct AC_MyStruct
{
	int ix;
	float fy;
	double dz;
	char cw;
};

union AC_MyUnion
{
	int ix;
	float fy;
	double dz;
	char cw;
};

int main(void)
{
	//variable Declarations
	struct AC_MyStruct ac_s;
	union AC_MyUnion ac_u;
	
	//code
	printf("\n");
	printf("Size of AC_MyStruct = %d\n", sizeof(ac_s));
	printf("\n");
	printf("Size of AC_MyUnion = %d\n", sizeof(ac_u));
	
	return (0);
}