#include <stdio.h>
#include <stdlib.h>

//macros
#define AC_NAME_LENGTH		100

//defining struct
struct Emp
{
	char name[AC_NAME_LENGTH];
	int age;
	char sex;
	float salary;
	char marital_status;
};

int main(void)
{
	//function declarations
	void AC_MyGetString(char[], int);

	//variable declarations
	struct Emp *pEmpRecords = NULL;
	int num_employee, ac_i;

	//code
	printf("\n");
	printf("Enter number of records for input: ");
	scanf("%d", &num_employee);

	//memory allocation
	pEmpRecords = (struct Emp *) malloc(sizeof(struct Emp) * num_employee);

	if(pEmpRecords == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation Failed: pEmpRecord\n");
		printf("Exiting...\n");
		exit(0);
	}

	else
	{
		printf("\n");
		printf("Memory Allocated:pEmpRecord\n");
	}

	//input data
	printf("\n");
	printf("User Input Data\n");

	for(ac_i = 0; ac_i < num_employee; ac_i++)
	{
		printf("\n\n");
		printf("--- Enter data for employee %d ---\n", ac_i + 1);

		printf("\n");
		printf("Enter employee name: ");
		AC_MyGetString(pEmpRecords[ac_i].name, AC_NAME_LENGTH);

		printf("\n");
		printf("Enter Age: ");
		scanf("%d", &pEmpRecords[ac_i].age);

		printf("\n");
		printf("Enter Sex (M/m: Male, F/f: Female):");
		scanf(" %c", &pEmpRecords[ac_i].sex);

		printf("\n");
		printf("Enter Marital Status:(Married: Y, Unmarried: N):");
		pEmpRecords[ac_i].marital_status = getch();
		printf("%c\n", pEmpRecords[ac_i].marital_status);
		pEmpRecords[ac_i].marital_status = toupper(pEmpRecords[ac_i].marital_status);

		printf("\n");
		printf("Enter Salary (INR):");
		scanf(" %f", &pEmpRecords[ac_i].salary);

	}

	//display data
	printf("\n\n");
	printf("--- Displaying Data ---\n");

		for(ac_i = 0; ac_i < num_employee; ac_i++)
	{
		printf("\n\n");
		printf("--- Employee Record %d ---\n", ac_i + 1);

		printf("\n");
		printf("NAME	: %s\n", pEmpRecords[ac_i].name);

		printf("AGE	: %d\n", pEmpRecords[ac_i].age);

		if(pEmpRecords[ac_i].sex == 'm' || pEmpRecords[ac_i].sex == 'M')
			printf("SEX	: Male\n");
		else if(pEmpRecords[ac_i].sex == 'f' || pEmpRecords[ac_i].sex == 'F')
			printf("SEX	: Female\n");
		else
			printf("Invalid Data Entered\n");

		if(pEmpRecords[ac_i].marital_status == 'Y')
			printf("MARITAL STATUS: Married\n");
		else if(pEmpRecords[ac_i].marital_status == 'N')
			printf("MARITAL STATUS: Unmarried\n");
		else
			printf("Invalid Data Entered\n");

		printf("SALARY IN INR:	%f\n", &pEmpRecords[ac_i].salary);
	}

	//freeing memory
	if(pEmpRecords)
	{
		free(pEmpRecords);
		pEmpRecords = NULL;
		printf("\n\n");
		printf("Memory Freed: pEmpRecords");
	}

	return(0);
}

void AC_MyGetString(char string[], int str_size)
{
	//variable declarations
	int ac_i;
	char ch = '\0';

	//code
	ac_i = 0;

	do
	{
		ch = getch();
		string[ac_i] = ch;
		printf("%c", string[ac_i]);
		ac_i++;
	}while((ch != '\r') && (ac_i < str_size));

	if(ac_i == str_size)
		string[ac_i - 1] = '\0';
	else
		string[ac_i] = '\0';
}
