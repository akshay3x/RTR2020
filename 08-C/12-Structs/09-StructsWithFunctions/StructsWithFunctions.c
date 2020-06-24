#include <stdio.h>

struct AC_MyData
{
	int ix;
	float fy;
	double dz;
	char cw;
};

int main (void)
{
	//function declaration
	struct AC_MyData AddStructMembers(struct AC_MyData, struct AC_MyData, struct AC_MyData);

	//variable declarations
	struct AC_MyData data1;
	struct AC_MyData data2;
	struct AC_MyData data3;
	struct AC_MyData answer_data;

	//code
	//data1
	printf("\n\n");
	printf("Enter Values for data1:\n");

	printf("Enter Integer value for i: ");
	scanf("%d", &data1.ix);

	printf("\n");
	printf("Enter float value for f: ");
	scanf("%f", &data1.fy);

	printf("\n");
	printf("Enter double value for d: ");
	scanf("%lf", &data1.dz);

	printf("\n");
	printf("Enter a character value for c: ");
	data1.cw = getch();

	//data2
	printf("\n\n");
	printf("Enter Values for data2:\n");

	printf("Enter Integer value for i: ");
	scanf("%d", &data2.ix);

	printf("\n");
	printf("Enter float value for f: ");
	scanf("%f", &data2.fy);

	printf("\n");
	printf("Enter double value for d: ");
	scanf("%lf", &data2.dz);

	printf("\n");
	printf("Enter a character value for c: ");
	data2.cw = getch();

	//data3
	printf("\n\n");
	printf("Enter Values for data3:\n");

	printf("Enter Integer value for i: ");
	scanf("%d", &data3.ix);

	printf("\n");
	printf("Enter float value for f: ");
	scanf("%f", &data3.fy);

	printf("\n");
	printf("Enter double value for d: ");
	scanf("%lf", &data3.dz);

	printf("\n");
	printf("Enter a character value for c: ");
	data3.cw = getch();

	answer_data = AddStructMembers(data1, data2, data3);

	printf("\n\n");
	printf("-----ANSWERS-----\n");
	printf("answer_data.i = %d\n", answer_data.ix);
	printf("answer_data.f = %f\n", answer_data.fy);
	printf("answer_data.d = %lf\n", answer_data.dz);

	answer_data.cw = data1.cw;
	printf("answer_data.c = %c\n", answer_data.cw);

	answer_data.cw = data2.cw;
	printf("answer_data.c = %c\n", answer_data.cw);

	answer_data.cw = data3.cw;
	printf("answer_data.c = %c\n", answer_data.cw);

	return(0);
}

struct AC_MyData AddStructMembers(struct AC_MyData d1, struct AC_MyData d2, struct AC_MyData d3)
{
	//variable declarations
	struct AC_MyData answer;

	answer.ix = d1.ix + d2.ix + d3.ix;
	answer.fy = d1.fy + d2.fy + d3.fy;
	answer.dz = d1.dz + d2.dz + d3.dz;

	return (answer);
}

