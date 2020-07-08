#include <stdio.h>

//defining struct
struct Mydata
{
	int ix;
	float fy;
	double dz;
};

int main(void)
{
	//variable declarations
	int int_size;
	int float_size;
	int double_size;
	int struct_Mydata_size;
	int pointer_to_struct_Mydata_size;

	struct Mydata *pData = NULL;

	//code
	//memory allocation
	pData = (struct Mydata *)malloc(sizeof(struct Mydata));

	if(pData == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation Failed: pData\n");
		printf("Exiting...\n");
		exit(0);
	}

	else
	{
		printf("\n\n");
		printf("Memory Allocated: pData");
	}

	//assigning values
	pData->ix = 70;
	pData->fy = 12.32323f;
	pData->dz = 1.232332;

	//displaying values of structure variable
	printf("\n\n");
	printf("Members of structure are:\n");
	printf("ix = %d\n", pData->ix);
	printf("fy = %f\n", pData->fy);
	printf("dz = %lf\n", pData->dz);

	//calculating sizes
	int_size = sizeof(pData->ix);
	float_size = sizeof(pData->fy);
	double_size = sizeof(pData->dz);

	//displaying size of data members
	printf("\n\n");
	printf("--- sizes of data members ---\n");
	printf("size of ix = %d\n", int_size);
	printf("size of fy = %d\n", float_size);
	printf("size of dz = %d\n", double_size);

	//calculating sizes of struct
	struct_Mydata_size = sizeof(struct Mydata);
	pointer_to_struct_Mydata_size = sizeof(struct Mydata *);

	//displaying sizes
	printf("\n");
	printf("size of struct Mydata = %d\n", struct_Mydata_size);
	printf("size of pointer to struct Mydata: %d\n", pointer_to_struct_Mydata_size);

	//freeing memory
	if(pData)
	{
		free(pData);
		pData = NULL;
		printf("\n\n");
		printf("Memory Freed: pData\n");
	}

	return(0);
}
