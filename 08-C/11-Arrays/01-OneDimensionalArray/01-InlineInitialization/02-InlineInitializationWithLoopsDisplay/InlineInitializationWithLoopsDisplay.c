#include <stdio.h>

int main(void)
{
	//variable declaraions
	int i_ac_Array[] = { 9, 30, 6, 12, 98, 95, 20, 23, 2, 45 };
	int i_ac_intSize;
	int i_ac_Array_size;
	int i_ac_Array_num_elements;
	
	float f_ac_Array[] = { 8.27f, 6.35f, 3.41f, 14.58f, 54.62f, 67.79f, 27.87f, 18.59f };
	int f_ac_floatSize;
	int f_ac_Array_size;
	int f_ac_Array_num_elements;

	char c_ac_Array[] = { 'A', 'S', 'T', 'R', 'O', 'M', 'E', 'D', 'I', 'C', 'O', 'M', 'P' };
	int c_ac_charSize;
	int c_ac_Array_size;
	int c_ac_Array_num_elements;
	int ac_i;

	//code
	// Integer variables Array[]
	printf("\n-----------------------------------------------------------------------------\n\n");
	printf("In-line Initialization And Loop (for) Display Of Elements of Array 'iArray[]': \n");
	
	i_ac_intSize = sizeof(int);
	i_ac_Array_size = sizeof(i_ac_Array);
	i_ac_Array_num_elements = i_ac_Array_size / i_ac_intSize;

	for (ac_i = 0; ac_i < i_ac_Array_num_elements; ac_i++)
	{
		printf("iArray[%2d] (Element %2d) = \t%d\n", ac_i, (ac_i + 1), i_ac_Array[ac_i]);
	}

	printf("\n");
	printf("Size Of int = %d bytes\n", i_ac_intSize);
	printf("Number Of Elements in 'int' Array 'iArray[]' = %d Elements\n", i_ac_Array_num_elements);
	printf("Size Of Array 'iArray[]' (%d Elements * %d Bytes) = %d Bytes\n\n", i_ac_Array_num_elements, i_ac_intSize, i_ac_Array_size);

	// Floating Point Variable Array[]
	printf("--------------------------------------------------------------------------------\n\n");
	printf("In-line Initialization And Loop (while) Display Of Elements of Array 'fArray[]':\n");
	
	f_ac_floatSize = sizeof(float);
	f_ac_Array_size = sizeof(f_ac_Array);
	f_ac_Array_num_elements = f_ac_Array_size / f_ac_floatSize;
	
	ac_i = 0;

	while(ac_i < f_ac_Array_num_elements)
	{
		printf("fArray[%2d] (Element %2d) = \t%f\n", ac_i, (ac_i + 1), f_ac_Array[ac_i]);
		ac_i++;
	}

	printf("\n");
	printf("Size Of float = %d bytes\n", f_ac_floatSize);
	printf("Number of elements in fArray[] = %d Elements\n", f_ac_Array_num_elements);
	printf("Size Of Array 'fArray[]' (%d Elements * %d Bytes) = %d Bytes\n\n", f_ac_Array_num_elements, f_ac_floatSize, f_ac_Array_size);

	//character variable Array[]
	printf("----------------------------------------------------------------------------------\n\n");
	printf("In-line Initialization And Loop (do while) Display Of Elements of Array 'cArray[]': \n");
	c_ac_charSize = sizeof(char);
	c_ac_Array_size = sizeof(c_ac_Array);
	c_ac_Array_num_elements = c_ac_Array_size / c_ac_charSize;
	ac_i = 0;
	
	do
	{
		printf("cArray[%2d] (Element %2d) = \t%c \n", ac_i, (ac_i + 1), c_ac_Array[ac_i]);
		ac_i++;
	} while (ac_i < c_ac_Array_num_elements);

	printf("\n");
	printf("Size Of char = %d bytes\n", c_ac_charSize);
	printf("Number of elements in cArray[] = %d Elements\n", c_ac_Array_num_elements);
	printf("Size Of Array 'cArray[]' (%d Elements * %d Bytes) = %d Bytes\n\n", c_ac_Array_num_elements, c_ac_charSize, c_ac_Array_size);

	printf("------------------------------------------------------------------------------\n");
	return(0);
}
