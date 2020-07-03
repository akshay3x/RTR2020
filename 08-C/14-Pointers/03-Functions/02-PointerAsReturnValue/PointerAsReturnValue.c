#include <stdio.h>
#include <stdlib.h>

//macro definitions
#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//function declarations
	char* ReplaceVowelWithHashSymbol(char *);

	//variable declarations
	char string[AC_MAX_STRING_LENGTH];
	char *char_replaced_string = NULL;

	//code
	//user input string
	printf("\n");
	printf("Enter String : ");
	gets_s(string, AC_MAX_STRING_LENGTH);

	//function call
	char_replaced_string = ReplaceVowelWithHashSymbol(string);

	if(char_replaced_string == NULL)
	{
		printf("\n");
		printf("ReplaceVowelWithHashSymbol() function failed\n");
		printf("Exiting...\n");
		exit(0);
	}

	//displaying replaced string
	printf("\n");
	printf("Replaced String is : %s\n", char_replaced_string);

	//freeing memory
	if(char_replaced_string)
	{
		free(char_replaced_string);
		char_replaced_string = NULL;
		printf("\n");
		printf("Memory Freed: char_replaced_string\n");
	}

	return(0);
}

char* ReplaceVowelWithHashSymbol(char *string)
{
	//function declarations
	void AcMyStrCpy(char *, char *);
	int AcMyStrLen(char *);

	//variable declarations
	char *char_new_string = NULL;
	int ac_i;

	//code
	//memory allocation
	char_new_string = (char *) malloc( AcMyStrLen(string)* sizeof(char));

	if(char_new_string == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed: char_new_string\n");
		return(NULL);
	}

	//copying string
	AcMyStrCpy(char_new_string, string);

	//replacing # for wovels in string
	for(ac_i = 0; ac_i < AcMyStrLen(char_new_string); ac_i++)
	{
		switch (char_new_string[ac_i])
		{
			case 'A':
			case 'a':
			case 'E' :
			case 'e' :
			case 'I' :
			case 'i' :
			case 'O' : 
			case 'o' :
			case 'U' :
			case 'u' :
				char_new_string[ac_i] = '#';
				break;
			default:
				break;
		}
	}

	return(char_new_string);
}

void AcMyStrCpy(char *dest_string, char *src_string)
{
	//function declarations
	int AcMyStrLen(char *);

	//variable Declarations
	int str_len;
	int ac_i;

	//code
	str_len = AcMyStrLen(src_string);

	for(ac_i = 0; ac_i < str_len; ac_i++)
	{
		*(dest_string + ac_i) = *(src_string + ac_i);
	}
	*(dest_string + ac_i) = '\0';
}

int AcMyStrLen(char *string)
{
	//variable declaration
	int ac_i;
	int str_len = 0;

	for(ac_i = 0; ac_i < AC_MAX_STRING_LENGTH; ac_i++)
	{
		if(string[ac_i] == '\0')
			break;
		else
			str_len++;
	}

	return(str_len);
}
