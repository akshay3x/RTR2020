#include <stdio.h>
#include <stdlib.h>

//macro definitions
#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//function declarations
	int AcMyStrCpy(char *, char *);
	int AcMyStrLen(char *);

	//variable declarations
	char *char_org_str = NULL;
	char *char_copy_str = NULL;
	int int_str_len;

	//code
	//memory allocation for org string
	char_org_str = (char *) malloc(sizeof(char) * AC_MAX_STRING_LENGTH);

	if(char_org_str == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed for Character String\n");
		printf("Exiting...\n");
		exit(0);
	}

	//user input
	printf("\n");
	printf("Enter a String : ");
	gets_s(char_org_str, AC_MAX_STRING_LENGTH);

	int_str_len = AcMyStrLen(char_org_str);

	//memory allocation for copy string
	char_copy_str = (char *) malloc(sizeof(char) * int_str_len);

	if(char_copy_str == NULL)
	{
		printf("\n");
		printf("Memory Allocation failed for copy string\n");
		printf("Exiting...\n");
		exit(0);
	}

	//function call
	AcMyStrCpy(char_copy_str, char_org_str);

	//displaying result
	printf("\n");
	printf("Entered String : %s\n", char_org_str);
	printf("\n");
	printf("Copied String : %s\n\n", char_copy_str);

	//freeing memory
	if(char_copy_str)
	{
		free(char_copy_str);
		char_copy_str = NULL;
		printf("Memory Freed: char_copy_str\n");
	}

	if(char_org_str)
	{
		free(char_org_str);
		char_org_str = NULL;
		printf("Memory Freed: char_org_str\n");
	}

	return (0);
}

int AcMyStrCpy(char *str_dest, char *str_src)
{
	//function declarations
	int AcMyStrLen(char *);

	//variable declarations
	int iStrLen = 0;
	int ac_i;

	//code
	iStrLen = AcMyStrLen(str_src);

	for(ac_i = 0; ac_i < iStrLen; ac_i++)
	{
		*(str_dest + ac_i) = *(str_src + ac_i);
	}

	*(str_dest + ac_i) = '\0';

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
	return(str_len);
}
