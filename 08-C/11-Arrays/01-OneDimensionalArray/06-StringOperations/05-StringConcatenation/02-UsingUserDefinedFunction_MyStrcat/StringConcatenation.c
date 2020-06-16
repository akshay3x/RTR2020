#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//Function Declarations/Prototype
	void AcMyStrCat(char[], char[]);

	//variable declarations
	char ch_ac_str_one[AC_MAX_STRING_LENGTH];
	char ch_ac_str_two[AC_MAX_STRING_LENGTH];

	//code
	printf("String Concatination:\n");
	printf("Enter a String:");
	gets_s(ch_ac_str_one, AC_MAX_STRING_LENGTH);

	printf("Enter another String:");
	gets_s(ch_ac_str_two, AC_MAX_STRING_LENGTH);

	printf("\n");
	printf("Before Concatination:\n");
	printf("String one: %s\n", ch_ac_str_one);

	printf("\n");
	printf("String Two: %s\n", ch_ac_str_two);

	//concatination function call
	AcMyStrCat(ch_ac_str_one, ch_ac_str_two);

	printf("\n");
	printf("After Concatination:\n");
	printf("String one: %s\n", ch_ac_str_one);

	printf("\n");
	printf("String Two: %s\n", ch_ac_str_two);

	return (0);
}

void AcMyStrCat(char str_one[], char str_two[])
{
	//function declarations/prototype
	int AcMyStrLen();

	//variable declarations
	int ac_j = 0, ac_i = 0;
	int istr_one_len = 0;
	int istr_two_len = 0;

	//code
	istr_one_len = AcMyStrLen(str_one);
	istr_two_len = AcMyStrLen(str_two);

	for(ac_i = istr_one_len, ac_j = 0; ac_j < istr_one_len; ac_i++, ac_j++)
	{
		str_one[ac_i] = str_two[ac_j];
	}
	str_one[ac_i] = '\0';
}

int AcMyStrLen(char str[])
{
	//variable declarations
	int i_ac_strlen = 0;
	int ac_j = 0;

	//code
	for(ac_j = 0; ac_j < AC_MAX_STRING_LENGTH; ac_j++)
	{
		if(str[ac_j] == '\0')
			break;
		else
			i_ac_strlen++;
	}
	return (i_ac_strlen);
}
