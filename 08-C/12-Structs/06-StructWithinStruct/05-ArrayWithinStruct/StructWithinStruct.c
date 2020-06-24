#include <stdio.h>

//structure definations 
struct AC_MyNumber
{
	int num;
	int num_table[10];
};

struct AC_NumTables
{
	struct AC_MyNumber a;
	struct AC_MyNumber b;
	struct AC_MyNumber c;
};

int main(void)
{
	//variable declarations
	struct AC_NumTables tables;
	int i = 0;

	//code
	tables.a.num = 3;
	for(i = 0; i < 10; i++)
		tables.a.num_table[i] = tables.a.num * (i + 1);

	tables.b.num = 5;
	for(i = 0; i < 10; i++)
		tables.b.num_table[i] = tables.b.num * (i + 1);

	tables.c.num = 7;
	for(i = 0; i < 10; i++)
		tables.c.num_table[i] = tables.c.num * (i + 1);

	printf("------------\n");
	printf("Table of %d:\n", tables.a.num);
	printf("------------\n");
	for(i = 0; i < 10; i++)
		printf("%d * %d = %d\n", i + 1, tables.a.num, tables.a.num_table[i]);

	printf("------------\n");
	printf("Table of %d:\n", tables.b.num);
	printf("------------\n");
	for(i = 0; i < 10; i++)
		printf("%d * %d = %d\n", i + 1, tables.b.num, tables.b.num_table[i]);

	printf("------------\n");
	printf("Table of %d:\n", tables.c.num);
	printf("------------\n");
	for(i = 0; i < 10; i++)
		printf("%d * %d = %d\n", i + 1, tables.c.num, tables.c.num_table[i]);

	return (0);
}
