#include <stdio.h>

#define AC_MAX_STRING_LENGTH	512

int main(void)
{
	//function declarations/prototype
	void AcMyStrRev(char[], char[]);
	
	//variable declarations
	char ch_ac_str_org[AC_MAX_STRING_LENGTH];
	char ch_ac_str_rev[AC_MAX_STRING_LENGTH];

	//code
	printf("\n");
	printf("Enter a String:");
	gets_s(ch_ac_str_org, AC_MAX_STRING_LENGTH);

	//function call
	AcMyStrRev(ch_ac_str_rev, ch_ac_str_org);

	printf("\n");
	printf("String entered: %s\n", ch_ac_str_org);

	printf("\n");
	printf("Reversed String: %s\n", ch_ac_str_rev);
	
	return (0);
}

void AcMyStrRev(char dest[], char src[])
{
	//function declarations/prototype
	int AcMyStrLen();
	
	//variable declarations
	int i_ac_strlen = 0;
	int ac_j = 0, ac_i = 0, rev_len;
	
	i_ac_strlen = AcMyStrLen(src);
	
	rev_len = i_ac_strlen - 1;
	
	for(ac_i = 0, ac_j = rev_len; ac_i < i_ac_strlen, ac_j >= 0; ac_i++, ac_j--)
	{
		dest[ac_i] = src[ac_j];
	}
	dest[ac_i]='\0';
	
}

int AcMyStrLen(char str[])
{
	//variable declarations
	int i_ac_strlen = 0;
	int ac_j = 0;
	
	//code
	for(ac_j=0; ac_j < AC_MAX_STRING_LENGTH; ac_j++)
	{
		if(str[ac_j] == '\0')
			break;
		else
			i_ac_strlen++;
	}
	
	return (i_ac_strlen);
	
}
