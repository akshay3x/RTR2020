#include <stdio.h>

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
	//variable declarations
	struct AC_MyStruct s1; 
	union AC_MyUnion u1;
	
	
	s1.ix = 800;
	s1.fy = 232.444;
	s1.dz = 93212.34;
	s1.cw = 'R';
	
	//code
	//MyStruct s1
	printf("-------------------------------\n\n");
	printf("Displaying members of AC_MyStruct s1:\n");
	printf("s1.i =		%d\n",  s1.ix);
	printf("s1.y =		%f\n",  s1.fy);
	printf("s1.d =		%lf\n", s1.dz);
	printf("s1.c =		%c\n",  s1.cw);
	
	printf("\n\n");
	printf("Diplaying Addresses of AC_MyStruct s1 members: \n");
	printf("s1.i =		%p\n", &s1.ix);
	printf("s1.y =		%p\n", &s1.fy);
	printf("s1.d =		%p\n", &s1.dz);
	printf("s1.c =		%p\n", &s1.cw);
	
	printf("AC_MyStruct s1 = 	%p\t", &s1);
	printf("size = 	%d\n",sizeof(s1));
	
	//MyUnion u1
	printf("-------------------------------\n\n");
	printf("Displaying members of AC_MyUnion u1:\n");
	
	u1.ix = 29;
	printf("u1.i =		%d\n", u1.ix);
	
	u1.fy = 23324.44;
	printf("u1.y =		%f\n", u1.fy);
	
	u1.dz = 2.312987;
	printf("u2.d =		%lf\n", u1.dz);
	
	u1.cw = 'K';
	printf("u1.c =		%c\n", u1.cw);

	printf("\n\n");
	printf("Diplaying Addresses of AC_MyUnion u1 members: \n");
	printf("u1.i =		%p\n", &u1.ix);
	printf("u1.y =		%p\n", &u1.fy);
	printf("u1.d =		%p\n", &u1.dz);
	printf("u1.c =		%p\n", &u1.cw);
	
	printf("AC_MyUnion u1 =	%p\t", &u1);
	printf("size = %d\n",sizeof(u1));
	
	return (0);
}

