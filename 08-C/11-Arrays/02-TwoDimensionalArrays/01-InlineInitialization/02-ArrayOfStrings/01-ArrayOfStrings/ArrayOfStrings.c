#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	int MyStrlen(char[]);
	
	char i_ac_strArray[10][15] = { "Hello!",
							  "Welcome",
							  "To", 
							  "Real", 
							  "Time",
							  "Rendering", 
							  "Batch", 
							  "(2020-21)", 
							  "Of", 
							  "ASTROMEDICOMP." };

	//IN-LINE INITIALIZATION
	int i_ac_char_size;
	int i_ac_strArray_size;
	int i_ac_num_elements, i_ac_num_rows, i_ac_num_columns;
	int i_ac_num_chars = 0;
	int ac_i;

	//code
	printf("\n\n");
	
	i_ac_char_size = sizeof(char);
	i_ac_strArray_size = sizeof(i_ac_strArray);
	i_ac_num_rows = i_ac_strArray_size / sizeof(i_ac_strArray[0]);  //row size
	i_ac_num_columns = sizeof(i_ac_strArray[0]) / i_ac_char_size;   //column size
	i_ac_num_elements = i_ac_num_rows * i_ac_num_columns;
	
	printf("Size of Array = %d \n\n", i_ac_strArray_size);
	printf("Number of Rows = %d\n\n", i_ac_num_rows);
	printf("Number of Columns = %d\n\n", i_ac_num_columns);
	printf("Maximum Number characters = %d \n\n", i_ac_num_elements);
	
	for (ac_i = 0; ac_i < i_ac_num_rows; ac_i++)
	{
		i_ac_num_chars = i_ac_num_chars + MyStrlen(i_ac_strArray[ac_i]);
	}

	printf("Actual Number of Characters = %d\n\n", i_ac_num_chars);

	printf("\n\n");
	printf("Strings In The 2D Array :");
	printf("%s ", i_ac_strArray[0]);
	printf("%s ", i_ac_strArray[1]);
	printf("%s ", i_ac_strArray[2]);
	printf("%s ", i_ac_strArray[3]);
	printf("%s ", i_ac_strArray[4]);
	printf("%s ", i_ac_strArray[5]);
	printf("%s ", i_ac_strArray[6]);
	printf("%s ", i_ac_strArray[7]);
	printf("%s ", i_ac_strArray[8]);
	printf("%s ", i_ac_strArray[9]);

	return(0);
}

int MyStrlen(char ac_str[])
{
	//variable declarations
	int ac_j;
	int ac_string_length = 0;

	for (ac_j = 0; ac_j < MAX_STRING_LENGTH; ac_j++)
	{
		if (ac_str[ac_j] == '\0')
			break;

		else
			ac_string_length++;
	}

	return(ac_string_length);
}
