#include <stdio.h>

#define AC_MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	int Ac_MyStrlen(char[]);
	
	char c_ac_strArray[10][15] = { "Hello!", 
							  "Welcome", 
							  "To", 
							  "Real", 
							  "Time",
							  "Rendering", 
							  "Batch", 
							  "(2020-21)", 
							  "Of", 
							  "ASTROMEDICOMP." }; //In-line initialization

	int i_ac_StrLengths[10]; //store lenths of strings at sequential indices 10 string= 10 lengths
	int i_ac_strArray_size;
	int i_ac_strArray_num_rows;
	int ac_i, ac_j;

	//code
	i_ac_strArray_size = sizeof(c_ac_strArray);
	i_ac_strArray_num_rows = i_ac_strArray_size / sizeof(c_ac_strArray[0]);

	//Storing in lengths of all the strings...
	for (ac_i = 0; ac_i < i_ac_strArray_num_rows; ac_i++)
		i_ac_StrLengths[ac_i] = Ac_MyStrlen(c_ac_strArray[ac_i]);

	printf("\n\n");
	printf("The Entire String Array :\n");
	for (ac_i = 0; ac_i < i_ac_strArray_num_rows; ac_i++)
		printf("%s ", c_ac_strArray[ac_i]);
	
	printf("\n\n");
	
	printf("Strings In The 2D Array : \n\n");
	for (ac_i = 0; ac_i < i_ac_strArray_num_rows; ac_i++)
	{
		printf("String Number %d => %s\n\n", (ac_i + 1), c_ac_strArray[ac_i]);
		for (ac_j = 0; ac_j < i_ac_StrLengths[ac_i]; ac_j++)
		{
			printf("Character %d = %c\n", (ac_j + 1), c_ac_strArray[ac_i][ac_j]);
		}
	printf("\n\n");
	}

	return(0);
}

int Ac_MyStrlen(char str[])
{
	//variable declarations
	int ac_j;
	int ac_string_length = 0;
	
	//code
	for (ac_j = 0; ac_j < AC_MAX_STRING_LENGTH; ac_j++)
	{
		if (str[ac_j] == '\0')
			break;

		else
			ac_string_length++;
	}

	return(ac_string_length);
}
