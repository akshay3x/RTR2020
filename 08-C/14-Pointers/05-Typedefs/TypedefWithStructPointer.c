#include <stdio.h>

//strucure definition
struct Mydata
{
	int ix;
	float fy;
	double dz;
};

int main(void)
{
	//variable declaration
	int int_size;
	int float_size;
	int double_size;
	int struct_Mydata_size;
	int ptr_to_struct_Mydata_size;

	//typedef
	typedef struct Mydata* MydataPtr;

	//variable of pointer typedef
	MydataPtr pData;

	//code
	//memory allocation
	pData = (MydataPtr) malloc(sizeof(struct Mydata));

	if(pData == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed: pData\n");
		printf("Exiting...\n");
		exit(0);
	}

	else
	{
		printf("\n");
		printf("Memory Allocated: pData\n");
	}

	//assigning values
	pData->ix = 12;
	pData->fy = 12.12f;
	pData->dz = 12.1212;

	//displaying data
	printf("\n");
	printf("ix = %d\n", pData->ix);
	printf("fy = %f\n", pData->fy);
	printf("dz = %lf\n", pData->dz);

	//calculating sizes
	int_size = sizeof(pData->ix);
	float_size = sizeof(pData->fy);
	double_size = sizeof(pData->dz);

	//displaying sizes
	printf("\n");
	printf("--- sizes in bytes ---\n");
	printf("size of ix = %d\n", int_size);
	printf("size of fy = %d\n", float_size);
	printf("size of dz = %d\n", double_size);

	//calculating size of struct Mydata
	struct_Mydata_size = sizeof(struct Mydata);
	ptr_to_struct_Mydata_size = sizeof(MydataPtr);

	//displaying sizes
	printf("\n");
	printf("size of struct Mydata = %d\n", struct_Mydata_size);
	printf("size of pointer to struct Mydata = %d\n", ptr_to_struct_Mydata_size);

	//freeing memory
	if(pData)
	{
		free(pData);
		pData = NULL;
		printf("\n");
		printf("Memory Freed: pData\n");
	}

	return(0);
}
