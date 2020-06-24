#include <stdio.h>

//macros
#define AC_NAME_LENGTH		100
#define AC_MARTAL_STATUS	10

#define AC_MAX_EMP_RECORDS	6

//structure definition
struct AC_MyEmployee
{
	char name[AC_NAME_LENGTH];
	int age;
	float salary;
	char sex;
	char marital_status;
};

int main(void)
{
	//function declarations
	void MygetStr(char[], int);
	
	//variable declarations
	struct AC_MyEmployee emp_rec[AC_MAX_EMP_RECORDS];
	int ac_i;
	
	//code
	//user data input of records
	for(ac_i = 0; ac_i < AC_MAX_EMP_RECORDS; ac_i++)
	{
		printf("\n");
		printf("Enter Name:");
		MygetStr(emp_rec[ac_i].name, AC_NAME_LENGTH);
		
		printf("\n");
		printf("Enter Age: ");
		scanf("%d", &emp_rec[ac_i].age);
		
		printf("Sex(M/F): ");
		scanf(" %c", &emp_rec[ac_i].sex);
		
		printf("Salary in Rs: ");
		scanf("%f", &emp_rec[ac_i].salary);
		
		printf("Marital Status (M/U): ");
		emp_rec[ac_i].marital_status = getch();
		printf("%c", emp_rec[ac_i].marital_status);
		emp_rec[ac_i].marital_status = toupper(emp_rec[ac_i].marital_status);
	}

	//displaying records
	printf("\n");
	printf("---------Emplyee Records----------------\n");
	
	for(ac_i = 0; ac_i < AC_MAX_EMP_RECORDS; ac_i++)
	{
		printf("======Record %d============\n",ac_i+1);
		printf("Name:		%s\n", emp_rec[ac_i].name);
		printf("Age:		%d Yrs.\n", emp_rec[ac_i].age);

		if(emp_rec[ac_i].sex == 'M' || emp_rec[ac_i].sex == 'm')
			printf("Sex:		Male.\n");
		else
			printf("Sex:		Female.\n");

		printf("Salary:		Rs %f.\n", emp_rec[ac_i].salary);
		if(emp_rec[ac_i].marital_status == 'M' || emp_rec[ac_i].marital_status == 'm' )
			printf("Marital Status:	Married");

		else if (emp_rec[ac_i].marital_status == 'U' || emp_rec[ac_i].marital_status == 'u')
			printf("Marital Status:	Unarried");

		else
			printf("Marital Status:	data input not correct");
		printf("\n");
	}

	return (0);
}

void MygetStr(char string[], int len)
{
	//variable declarations
	int i;
	char ch = '\0';

	//code
	i = 0;
	do
	{
		ch = getch();
		string[i] = ch;
		printf("%c", string[i]);
		i++;
		
	} while((ch != '\r' ) && (i < len));
		
	if(i == len)
		string[i-1] = '\0';
	else
		string[i] = '\0';
}

