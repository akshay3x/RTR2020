#include <stdio.h>

//macros
#define AC_NAME_LENGTH		100
#define AC_MARTAL_STATUS	10

//Strture Definition
struct AC_MyEmployee
{
	char name[AC_NAME_LENGTH];
	int age;
	float salary;
	char sex;
	char marital_status[AC_MARTAL_STATUS];
};


int main(void)
{
	//variable declarations
	struct AC_MyEmployee emp_rec[5];
	
	char employee_akshay[]  = "Akshay";
	char employee_vishal[]  = "Vishal";
	char employee_ajit[]    = "Ajit";
	char employee_neha[]    = "Neha";
	char employee_ashvini[] = "Ashvini";

	int ac_i;

	//code
	//hardcoded initialization of struct array
	//Employee 1
	strcpy(emp_rec[0].name, employee_akshay);
	emp_rec[0].age = 28;
	emp_rec[0].sex = 'M';
	emp_rec[0].salary = 40000.0f;
	strcpy(emp_rec[0].marital_status, "Unmarried");

	//Employee 2
	strcpy(emp_rec[1].name, employee_vishal);
	emp_rec[1].age = 29;
	emp_rec[1].sex = 'M';
	emp_rec[1].salary = 45000.0f;
	strcpy(emp_rec[1].marital_status, "Married");

	//Employee 3
	strcpy(emp_rec[2].name, employee_ajit);
	emp_rec[2].age = 28;
	emp_rec[2].sex = 'M';
	emp_rec[2].salary = 40000.0f;
	strcpy(emp_rec[2].marital_status, "Unmarried");

	//Employee 4
	strcpy(emp_rec[3].name, employee_neha);
	emp_rec[3].age = 27;
	emp_rec[3].sex = 'F';
	emp_rec[3].salary = 45000.0f;
	strcpy(emp_rec[3].marital_status, "Married");

	//Employee 5
	strcpy(emp_rec[4].name, employee_ashvini);
	emp_rec[4].age = 27;
	emp_rec[4].sex = 'F';
	emp_rec[4].salary = 45000.0f;
	strcpy(emp_rec[4].marital_status, "Unmarried");

	//displaying records
	printf("\n");
	printf("---------Emplyee Records----------------\n");

	for(ac_i = 0; ac_i < 5; ac_i++)
	{
		printf("======Record %d============\n",ac_i+1);
		printf("Name:		%s.\n",emp_rec[ac_i].name);
		printf("Age:		%d Yrs.\n",emp_rec[ac_i].age);
		if(emp_rec[ac_i].sex == 'M' || emp_rec[ac_i].sex == 'm')
			printf("Sex:		Male.\n");
		else
			printf("Sex:		Female.\n");
		printf("Salary:		Rs %f.\n", emp_rec[ac_i].salary);
		printf("Marital Status:	%s.\n", emp_rec[ac_i].marital_status);
		
		printf("\n");
	}

	return (0);
}
