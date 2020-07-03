#include <stdio.h>

int main(void)
{
	//variable declarations
	FILE *pFile = NULL;

	//code
	//opening a file
	if(fopen_s(&pFile, "ARC_Log.txt", "w") != 0)
	{
		printf("Can not open desired file\n");
		exit(0);
	}
	printf("\n");
	printf("File Opened\n");

	//writing into file
	fprintf(pFile, "India Is My Country.\n");
	printf("\n");
	printf("Message Written In File\n");

	//closing file
	fclose(pFile);
	pFile = NULL;

	printf("\n");
	printf("File Closed\n");

	return(0);
}
