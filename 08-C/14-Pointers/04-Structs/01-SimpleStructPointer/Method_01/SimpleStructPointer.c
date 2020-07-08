#include <stdio.h>

//defining Structure
struct Mydata
{
	int ix;
	float fy;
	double dz;
};

int main(void)
{
	//varaible declarations
	int int_size;
	int float_size;
	int double_size;
	int struct_Mydata_size;
	int ptr_to_struct_Mydata_size;

	struct Mydata *pData = NULL;

	//code
	//memory allocation
	pData = (struct Mydata *) malloc(sizeof(struct Mydata));

	if(pData == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed: pData struct Mydata\n");
		printf("Exiting...\n");
		exit(0);
	}

	else
	{
		printf("\n");
		printf("Memory Allocated: pData struct Mydata\n");
	}

	//assigning data values
	(*pData).ix = 30;
	(*pData).fy = 11.25f;
	(*pData).dz = 1.2995;

	//Displaying Values of Data members of structure
	printf("\n\n");
	printf("Data members od struct Mydata are:\n");
	printf("ix = %d\n", (*pData).ix);
	printf("fy = %f\n", (*pData).fy);
	printf("dz = %lf\n", (*pData).dz);

	//calculating sizes in bytes of members
	int_size = sizeof((*pData).ix);
	float_size = sizeof((*pData).fy);
	double_size = sizeof((*pData).dz);

	//displaying sizes
	printf("\n\n");
	printf("--- sizes in bytes ---\n");
	printf("size of ix = %d bytes\n", int_size);
	printf("size of fy = %d bytes\n", float_size);
	printf("size of dz = %d bytes\n", double_size);

	//calculating size for entire structure
	struct_Mydata_size = sizeof(struct Mydata);
	ptr_to_struct_Mydata_size = sizeof(struct Mydata *);

	//Displaying sizes in bytes for entire struct mydata
	printf("\n\n");
	printf("size of struct Mydata: %d bytes\n", struct_Mydata_size);
	printf("size of pointer to struct Mydata: %d bytes\n", ptr_to_struct_Mydata_size);

	//freeeing memory
	if(pData)
	{
		free(pData);
		pData = NULL;
		printf("\n\n");
		printf("Memory Freed: pData\n");
	}

	return(0);
}
