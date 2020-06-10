#include <stdio.h>

#define AC_MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype/declaration
	void AcMyStrcpy(char[], char[]);

	//variable declaraions
	char c_ac_strArray[5][10];
	int i_ac_char_size;
	int i_ac_strArray_size;
	int i_ac_num_elements, i_ac_num_rows, i_ac_num_columns;
	int ac_i;

	//code
	printf("\n\n");
	i_ac_char_size = sizeof(char);
	i_ac_strArray_size = sizeof(c_ac_strArray);
	i_ac_num_rows = i_ac_strArray_size / sizeof(c_ac_strArray[0]);
	i_ac_num_columns = sizeof(c_ac_strArray[0]) / i_ac_char_size;
	i_ac_num_elements = i_ac_num_rows * i_ac_num_columns;
	
	printf("Size of Array = %d\n", i_ac_strArray_size);
	printf("Number of Rows = %d\n", i_ac_num_rows);
	printf("Number of Columns = %d\n", i_ac_num_columns);
	printf("Maximum Number of Elements in Array = %d\n\n", i_ac_num_elements);


	AcMyStrcpy(c_ac_strArray[0], "My");
	AcMyStrcpy(c_ac_strArray[1], "Name");
	AcMyStrcpy(c_ac_strArray[2], "Is");
	AcMyStrcpy(c_ac_strArray[3], "Akshay");
	AcMyStrcpy(c_ac_strArray[4], "Chandawale.");

	printf("\n");
	printf("Strings is: ");
	for (ac_i = 0; ac_i < i_ac_num_rows; ac_i++)
		printf("%s ", c_ac_strArray[ac_i]);

	printf("\n");

	return(0);
}


void AcMyStrcpy(char str_destination[], char str_source[])
{
	//function prototype/declaration
	int AcMyStrlen(char[]);

	//variable declarations
	int iStringLength = 0;
	int j;

	//code
	iStringLength = AcMyStrlen(str_source);
	
	for (j = 0; j < iStringLength; j++)
		str_destination[j] = str_source[j];
	
	str_destination[j] = '\0';

}

int AcMyStrlen(char str[])
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
