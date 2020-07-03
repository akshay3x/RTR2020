#include <stdio.h>
#include <stdlib.h>

//macro definitions
#define AC_MAX_STRING_LENGTH 512

int main (void)
{
	//function declarations
	int AcMyStrLen(char *);
	
	//variable declarations
	char *char_str = NULL;
	int iStrLength;

	//code
	//memory allocation
	char_str = (char *) malloc(sizeof(char) * AC_MAX_STRING_LENGTH);

	if(char_str == NULL)
	{
		printf("\n");
		printf("Memory allocation failed for character string\nExiting...\n");
		exit(0);
	}

	else
	{
		printf("\n");
		printf("Memory Allocation Successful for character string\n");
	}

	//string input
	printf("\n");
	printf("Enter a string: ");
	gets_s(char_str, AC_MAX_STRING_LENGTH);

	//displaying string
	printf("\n");
	printf("Entered String : ");
	printf("%s\n", char_str);

	//function call
	iStrLength = AcMyStrLen(char_str);

	printf("\n");
	printf("Length of string = %d\n", iStrLength);

	//freeing memory
	if(char_str)
	{
		free(char_str);
		char_str = NULL;
	}

	return (0);
}

int AcMyStrLen(char *str)
{
	//variable declarations
	int ac_i;
	int str_len = 0;

	//code
	for(ac_i = 0; ac_i < AC_MAX_STRING_LENGTH; ac_i++)
	{
		if(str[ac_i] == '\0')
			break;
		else
			str_len++;
	}

	return (str_len);
}
