#include <stdio.h>

int main(void)
{
	//variable declaraions
	char c_ac_strArray[5][12];
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
	
	printf("Size Of Array  = %d \n", i_ac_strArray_size);
	printf("Number of Rows = %d\n", i_ac_num_rows);
	printf("Number of Columns = %d\n", i_ac_num_columns);
	printf("Maximum Number of Elements = %d\n", i_ac_num_elements);

	// -----ROW 1 / STRING 1 ----
	c_ac_strArray[0][0] = 'M';
	c_ac_strArray[0][1] = 'y';
	c_ac_strArray[0][2] = '\0'; //NULL-TERMINATING 
	
	// -----ROW 2 / STRING 2 ----
	c_ac_strArray[1][0] = 'n';
	c_ac_strArray[1][1] = 'a';
	c_ac_strArray[1][2] = 'm';
	c_ac_strArray[1][3] = 'e';
	c_ac_strArray[1][4] = '\0'; //NULL-TERMINATING 
	
	// -----ROW 3 / STRING 3 ----
	c_ac_strArray[2][0] = 'i';
	c_ac_strArray[2][1] = 's';
	c_ac_strArray[2][2] = '\0'; //NULL-TERMINATING 
	
	// -----ROW 4 / STRING 4 ----
	c_ac_strArray[3][0] = 'A';
	c_ac_strArray[3][1] = 'k';
	c_ac_strArray[3][2] = 's';
	c_ac_strArray[3][3] = 'h';
	c_ac_strArray[3][4] = 'a';
	c_ac_strArray[3][5] = 'y';
	c_ac_strArray[3][6] = '\0'; //NULL-TERMINATING 
	
	// -----ROW 4 / STRING 4 ----
	c_ac_strArray[4][0] = 'C';
	c_ac_strArray[4][1] = 'h';
	c_ac_strArray[4][2] = 'a';
	c_ac_strArray[4][3] = 'n';
	c_ac_strArray[4][4] = 'd';
	c_ac_strArray[4][5] = 'a';
	c_ac_strArray[4][6] = 'w';
	c_ac_strArray[4][7] = 'a';
	c_ac_strArray[4][8] = 'l';
	c_ac_strArray[4][9] = 'e';
	c_ac_strArray[4][10] = '.';
	c_ac_strArray[4][11] = '\0'; //NULL-TERMINATING 
	
	printf("\n");
	printf("All combined String is: ");
	
	for (ac_i = 0; ac_i < i_ac_num_rows; ac_i++)
		printf("%s ", c_ac_strArray[ac_i]);
	
	printf("\n");
	
	return(0);
}
