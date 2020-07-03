#include <stdio.h>

//macro definitions
#define AC_MAX_STRING_LENGTH		512

int main(void)
{
	//function declarations
	void AcMyStrCat(char *, char *);
	int AcMyStrLen(char *);

	//variable declarations
	char *char_array_one = NULL;
	char *char_array_two = NULL;

	//code
	//memory allocation 
	char_array_one = (char *) malloc(AC_MAX_STRING_LENGTH * sizeof(char));

	if(char_array_one == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed : char_array_one\n");
		printf("Exiting...\n");
		exit(0);
	}

	//user input string
	printf("\n");
	printf("Enter 1st String: ");
	gets_s(char_array_one, AC_MAX_STRING_LENGTH);

	//memory allocation
	char_array_two = (char *) malloc(AC_MAX_STRING_LENGTH * sizeof(char));

	if(char_array_two == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed: char_array_two\n");
		printf("Exiting...\n");
		exit(0);
	}

	//user input string
	printf("\n");
	printf("Enter 2nd String: ");
	gets_s(char_array_two, AC_MAX_STRING_LENGTH);

	//before concatenation
	printf("\n\n");
	printf("--- BEFORE CONCATENATION ---\n");
	printf(" 1st String: %s\n", char_array_one);
	printf(" 2nd String: %s\n", char_array_two);

	//function call
	AcMyStrCat(char_array_one, char_array_two);

	//after concatenation
	printf("\n\n");
	printf("--- AFTER CONCATENATION ---\n");
	printf(" 1st String: %s\n", char_array_one);
	printf(" 2nd String: %s\n\n", char_array_two);

	//freeing memory
	if(char_array_two)
	{
		free(char_array_two);
		char_array_two = NULL;
		printf("Memory Freed: char_array_two\n");
	}

	if(char_array_one)
	{
		free(char_array_one);
		char_array_one = NULL;
		printf("Memory Freed: char_array_one\n");
	}

	return (0);
}

void AcMyStrCat(char *dest_string, char *src_string)
{
	//Function declarations
	int AcMyStrLen(char *);

	//variable declarations
	int iStrLenSrc = 0;
	int iStrLenDest = 0;
	int ac_i, ac_j;

	//code
	iStrLenDest = AcMyStrLen(dest_string);
	iStrLenSrc = AcMyStrLen(src_string);

	for(ac_i = iStrLenDest, ac_j = 0; ac_j < iStrLenSrc; ac_i++, ac_j++)
	{
		 *(dest_string + ac_i) = *(src_string + ac_j);
	}
	*(dest_string + ac_i) = '\0';

}

int AcMyStrLen(char *string)
{
	//variable declarations
	int ac_i;
	int str_len = 0;

	//code
	for(ac_i = 0; ac_i < AC_MAX_STRING_LENGTH; ac_i++)
	{
		if(string[ac_i] == '\0')
			break;
		else
			str_len++;
	}

	return(str_len);
}
