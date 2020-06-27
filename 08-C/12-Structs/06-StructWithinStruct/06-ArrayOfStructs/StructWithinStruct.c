#include <stdio.h>

//structure declarations
struct AC_Mynumber
{
	int num_tables[10];
	int num;
};

struct AC_numTables
{
	struct AC_Mynumber n1;
};

int main(void)
{
	
	//variable declarations
	struct AC_numTables tables2[10];
	int i, j;

	//code
	for(i = 0; i < 10; i++)
	{
		tables2[i].n1.num = (i + 1);
	}

	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			tables2[i].n1.num_tables[j] =  tables2[i].n1.num * (j + 1);
		}
	}

	for(i = 0; i < 10; i++)
	{
		printf("--------------\n");
		printf("Table of %d :\n", tables2[i].n1.num);
		printf("--------------\n");
		for(j = 0; j < 10; j++)
		{
			printf("%d * %d = %d\n", j + 1, tables2[i].n1.num, tables2[i].n1.num_tables[j]);
		}
	}

	return (0);
}
