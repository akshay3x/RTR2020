#include <stdio.h>

union AC_MyUnion
{
	int ix;
	float fy;
	double dz;
	char cw;
};

int main(void)
{
	//variable declarations
	union AC_MyUnion u1;
	union AC_MyUnion u2;

	u1.ix = 6;
	u1.fy = 23.2444;
	u1.dz = 93.21234;
	u1.cw = 'A';

	//code
	//MyUnion u1
	printf("\n");
	printf("-------------------------------\n");
	printf("Displaying members of AC_MyUnion u1:\n");
	printf("u1.i =		%d\n", u1.ix);
	printf("u1.y =		%f\n", u1.fy);
	printf("u1.d =		%lf\n", u1.dz);
	printf("u1.c =		%c\n", u1.cw);

	printf("\n\n");
	printf("Diplaying Addresses of AC_MyUnion u1 members: \n");
	printf("u1.i =		%p\n", &u1.ix);
	printf("u1.y =		%p\n", &u1.fy);
	printf("u1.d =		%p\n", &u1.dz);
	printf("u1.c =		%p\n", &u1.cw);

	printf("AC_MyUnion u1 = %p\t", &u1);
	printf("size = 	%d\n", sizeof(u1));

	//MyUnion u2
	printf("-------------------------------\n\n");
	printf("Displaying members of AC_MyUnion u2:\n");

	u2.ix = 9;
	printf("u2.i =		%d\n", u2.ix);

	u2.fy = 233.2444;
	printf("u2.y =		%f\n", u2.fy);

	u2.dz = 231.2987;
	printf("u2.d =		%lf\n", u2.dz);

	u2.cw = 'C';
	printf("u2.c =		%c\n", u2.cw);

	printf("\n\n");
	printf("Diplaying Addresses of AC_MyUnion u2 members: \n");
	printf("u2.i =		%p\n", &u2.ix);
	printf("u2.y =		%p\n", &u2.fy);
	printf("u2.d =		%p\n", &u2.dz);
	printf("u2.c =		%p\n", &u2.cw);

	printf("AC_MyUnion u2 =	%p\t", &u2);
	printf("size = %d\n",sizeof(u2));

	return (0);
}

