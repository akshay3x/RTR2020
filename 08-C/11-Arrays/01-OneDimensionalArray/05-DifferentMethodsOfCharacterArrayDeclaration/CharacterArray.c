#include <stdio.h>

int main(void)
{
	//variable declarations
	char ch_ac_Array_01[]  = { 'A', 'S', 'T', 'R', 'O', 'M', 'E', 'D', 'I', 'C', 'O', 'M', 'P', '\0' }; 
	char ch_ac_Array_02[9] = { 'W', 'E', 'L', 'C', 'O', 'M', 'E', 'S', '\0' };
	char ch_ac_Array_03[]  = { 'Y', 'O', 'U', '\0' }; 
	char ch_ac_Array_04[]  = "To"; //here \0 added/taken bydefault, size will be 3, chars 2.
	char ch_ac_Array_05[]  = "REAL TIME RENDERING BATCH OF 2020-21"; //here \0 added/taken bydefault
	char ch_ac_Array_WithoutNullTerminator[] = { 'H', 'e', 'l', 'l', 'o' };

	//code
	printf("\n\n");
	
	printf("Size Of chArray01 : %lu\n\n", sizeof(ch_ac_Array_01));
	printf("Size Of chArray02 : %lu\n\n", sizeof(ch_ac_Array_02));
	printf("Size Of chArray03 : %lu\n\n", sizeof(ch_ac_Array_03));
	printf("Size Of chArray04 : %lu\n\n", sizeof(ch_ac_Array_04));
	printf("Size Of chArray05 : %lu\n\n", sizeof(ch_ac_Array_05));

	printf("\n\n");
	
	printf("The Strings Are : \n\n");
	printf("chArray01 : %s\n\n", ch_ac_Array_01);
	printf("chArray02 : %s\n\n", ch_ac_Array_02);
	printf("chArray03 : %s\n\n", ch_ac_Array_03);
	printf("chArray04 : %s\n\n", ch_ac_Array_04);
	printf("chArray05 : %s\n\n", ch_ac_Array_05);

	printf("\n\n");

	printf("Size Of chArray_WithoutNullTerminator : %lu\n\n", sizeof(ch_ac_Array_WithoutNullTerminator));
	printf("chArray_WithoutNullTerminator : %s\n\n",ch_ac_Array_WithoutNullTerminator);

	return(0);
}
