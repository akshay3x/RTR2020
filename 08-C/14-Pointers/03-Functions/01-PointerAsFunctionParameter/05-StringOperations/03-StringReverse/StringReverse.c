#include <stdio.h>
#include <stdlib.h>

//macro definitions
#define AC_MAX_STRING_LENGTH 512

int main(void)
{
	//function declarations
	void AcMyStrRev(char *, char *);
	int AcMyStrLen(char *);

	//varable declarations
	char *char_org_str = NULL;
	char *char_rev_str = NULL;
	int org_str_len = 0;

	//code
	//memory allocation for org string
	char_org_str = (char *) malloc(sizeof(char) * AC_MAX_STRING_LENGTH);

	if(char_org_str == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed: char_org_str\n");
		printf("Exiting...\n");
		exit(0);
	}

	printf("\n");
	printf("Enter string : ");
	gets_s(char_org_str, AC_MAX_STRING_LENGTH);

	printf("\n");
	printf("Enterd stirng : %s\n", char_org_str);

	org_str_len = AcMyStrLen(char_org_str);

	//memory allocation for reverse string
	char_rev_str = (char *) malloc(sizeof(char) * org_str_len);

	if(char_rev_str == NULL)
	{
		printf("\n");
		printf("Memory Allocation Failed: char_rev_str\n");
		printf("Exiting...\n");
		exit(0);
	}

	//function call
	AcMyStrRev(char_rev_str, char_org_str);

	//displaying strings
	printf("\n");
	printf("Entered String : %s\n", char_org_str);

	printf("\n");
	printf("Reversed String : %s\n\n", char_rev_str);

	//freeing memory
	if(char_rev_str)
	{
		free(char_rev_str);
		char_rev_str = NULL;
		printf("Memory Freed: char_rev_str\n");
	}

	if(char_org_str)
	{
		free(char_org_str);
		char_org_str = NULL;
		printf("Memory Freed: char_org_str\n");
	}

	return (0);
}

void AcMyStrRev(char *dest_string, char *src_string)
{
	//function declarations
	int AcMyStrLen(char *);

	//varable Declarations
	int ac_i, ac_j;
	int iStrLen = 0, len;

	//code
	iStrLen = AcMyStrLen(src_string);

	len = iStrLen - 1;

	for(ac_i = 0, ac_j = len; ac_i < len, ac_j >= 0; ac_i++, ac_j--)
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

