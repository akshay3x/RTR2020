#include <stdio.h>

#define AC_MAX_NAME_LENGTH	512

struct employee
{
	char name[AC_MAX_NAME_LENGTH];
	unsigned int age;
	char gender;
	double salary;
};

struct mydata
{
	int ix;
	float fy;
	double dz;
	char ca;
};

int main(void)
{
	//typedefs
	typedef struct employee AC_EMPLOYEE;
	typedef struct mydata AC_DATA;

	//variable declarations
	struct employee emp = {"James", 25, 'M', 10000.00};
	AC_EMPLOYEE emp_typedef = {"Lily", 23, 'F', 30000};

	struct mydata data = {12, 32.65f, 32.21452, 'A'};
	AC_DATA data_typedef = {10, 78.35f, 65.3254, 'D'};

	printf("\n--------------------\n");
	printf("struct employee:\n");
	printf("emp.name:	%s\n", emp.name);
	printf("emp.age:	%d\n", emp.age);
	printf("emp.gender:	%c\n", emp.gender);
	printf("emp.salary:	%lf\n", emp.salary);

	printf("\n--------------------\n");
	printf("AC_EMPLOYEE:\n");
	printf("emp_typedef.name:	%s\n", emp_typedef.name);
	printf("emp_typedef.age:	%d\n", emp_typedef.age);
	printf("emp_typedef.gender:	%c\n", emp_typedef.gender);
	printf("emp_typedef.salary:	%lf\n", emp_typedef.salary);

	printf("\n--------------------\n");
	printf("struct mydata:\n");
	printf("data.i:		%d\n", data.ix);
	printf("data.f:		%f\n", data.fy);
	printf("data.d:		%lf\n", data.dz);
	printf("data.c:		%c\n", data.ca);

	printf("\n--------------------\n");
	printf("AC_DATA:\n");
	printf("data_typedef.i:		%d\n", data_typedef.ix);
	printf("data_typedef.f:		%f\n", data_typedef.fy);
	printf("data_typedef.d:		%lf\n", data_typedef.dz);
	printf("data_typedef.c:		%c\n", data_typedef.ca);

	printf("--------------------\n");
	return (0);
}
