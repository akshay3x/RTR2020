#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//function declarations
	int AcMyStringLenght(char[]);

	//variable declarations
	char ch_input_string[AC_MAX_STRING_LENGTH];
	int i_input_strlen;
	int ac_i;
	int iword_count = 0;
	int ispace_count = 0;

	//code
	printf("\n");
	printf("Enter a String:");
	gets_s(ch_input_string, AC_MAX_STRING_LENGTH);

	i_input_strlen = AcMyStringLenght(ch_input_string);

	for(ac_i = 0; ac_i < i_input_strlen; ac_i++)
	{
		switch (ch_input_string[ac_i])
		{
			case 32:
				ispace_count++;
				break;
			
			default:
				break;
		}
	}

	iword_count = ispace_count + 1;

	printf("\n");
	printf("Input String:%s\n", ch_input_string);
	
	printf("Space Count: %d\n", ispace_count);
	printf("Word Count: %d\n", iword_count);

	return (0);
}

int AcMyStringLenght(char str[])
{
	//variable declarations
	int ac_i;
	int istrlen = 0;

	//code
	for(ac_i = 0; ac_i < AC_MAX_STRING_LENGTH; ac_i++)
	{
		if(str[ac_i] == '\0')
			break;
		else
			istrlen++;
	}

	return (istrlen);
}
