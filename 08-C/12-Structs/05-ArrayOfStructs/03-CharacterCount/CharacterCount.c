#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define AC_MAX_STRING_LENGTH	1024

//defining structure
struct AC_chars_counts
{
	char ch;
	int ch_count;
} char_count[] = 	{	{'A', 0},
						{'B', 0},
						{'C', 0},
						{'D', 0},
						{'E', 0},
						{'F', 0},
						{'G', 0},
						{'H', 0},
						{'I', 0},
						{'J', 0},
						{'K', 0},
						{'L', 0},
						{'M', 0},
						{'N', 0},
						{'O', 0},
						{'P', 0},
						{'Q', 0},
						{'S', 0},
						{'T', 0},
						{'U', 0},
						{'V', 0},
						{'W', 0},
						{'X', 0},
						{'Y', 0},
						{'Z', 0},
					};

//macros for size calculations 
#define SIZE_OF_ARRAY_OF_STRUCT_CHAR_COUNT	sizeof(char_count)

#define SIZE_OF_ONE_STRUCT_OF_CHAR_COUNT 	sizeof(char_count[0])

#define NUMBER_OF_ELEMENTS_IN_STRUCT_ARRAY	(SIZE_OF_ARRAY_OF_STRUCT_CHAR_COUNT /SIZE_OF_ONE_STRUCT_OF_CHAR_COUNT)


int main(void)
{

	//variable declarations
	char ch_input_string[AC_MAX_STRING_LENGTH];
	int j, i;
	int actual_str_length = 0;

	//code
	printf("\n");
	printf("Enter a String: ");
	gets_s(ch_input_string, AC_MAX_STRING_LENGTH);

	actual_str_length = strlen(ch_input_string);

	printf("\n");
	printf("Entered String: %s", ch_input_string);

	for(i = 0; i < actual_str_length; i++)
	{
		for(j = 0; j < NUMBER_OF_ELEMENTS_IN_STRUCT_ARRAY ; j++)
		{
			ch_input_string[i] = toupper(ch_input_string[i]);
			
			if(ch_input_string[i] == char_count[j].ch)
				char_count[j].ch_count++;
		}
	}

	printf("\n");
	printf("the occureance of characters in input string:\n");
	printf("character \tcount");

	for(i = 0; i < NUMBER_OF_ELEMENTS_IN_STRUCT_ARRAY ; i++)
	{
		if(char_count[i].ch_count > 0)
		{
			printf("\n");
			printf("%c		%d", char_count[i].ch, char_count[i].ch_count);
		}
	}

	printf("\n");
	return (0);
}
