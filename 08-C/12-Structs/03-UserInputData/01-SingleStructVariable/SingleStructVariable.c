#include <stdio.h>

struct AcMyData
{
	int ix;
	float fy;
	double dz;
	char ch;
};

int main(void)
{
	struct AcMyData data;

	//code
	printf("\n");
	printf("Enter integer value for data.i:");
	scanf("%d", &data.ix);

	printf("\n");
	printf("Enter float value for data.f:");
	scanf("%f", &data.fy);

	printf("\n");
	printf("Enter double value for data.d:");
	scanf("%lf", &data.dz);

	printf("\n");
	printf("Enter character value for data.c:");
	data.ch = getch();

	printf("\n\n");
	printf("Diaplaying members of structure variable\n");
	printf("data.i = %d\n", data.ix);
	printf("data.f = %f\n", data.fy);
	printf("data.d = %lf\n", data.dz);
	printf("data.c = %c\n", data.ch);

	return (0);
}

