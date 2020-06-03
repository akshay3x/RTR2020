#include <stdio.h>
#include <conio.h>

// ASCII Values: 'A' -> 'Z' => 65 -> 90
#define CHAR_ALPHABET_UPPER_CASE_BEGINNING 	65
#define CHAR_ALPHABET_UPPER_CASE_ENDING 	90

// ASCII Values:'a'-> 'z' => 97 -> 122
#define CHAR_ALPHABET_LOWER_CASE_BEGINNING 	97
#define CHAR_ALPHABET_LOWER_CASE_ENDING 	122

// ASCII Values: '0' -> '9' => 48 -> 57
#define CHAR_DIGIT_BEGINNING 	48
#define CHAR_DIGIT_ENDING 		57

int main(void)
{
	//variable declarations
	char ac_ch;
	int ac_ch_value;
	
	//code
	printf("Enter a character: ");
	ac_ch = getch();
	printf("\n\n");

	if ((ac_ch == 'A' || ac_ch == 'a') ||
		(ac_ch == 'E' || ac_ch == 'e') ||
		(ac_ch == 'I' || ac_ch == 'i') ||
		(ac_ch == 'O' || ac_ch == 'o') ||
		(ac_ch == 'U' || ac_ch == 'u'))
	{
	printf("Character \'%c\' is a VOWEL character!\n", ac_ch);
	}

	else
	{
		ac_ch_value = (int)ac_ch;

		if (((ac_ch_value >= CHAR_ALPHABET_UPPER_CASE_BEGINNING) &&
			 (ac_ch_value <= CHAR_ALPHABET_UPPER_CASE_ENDING)) ||
			((ac_ch_value >= CHAR_ALPHABET_LOWER_CASE_BEGINNING) &&
			 (ac_ch_value  <= CHAR_ALPHABET_LOWER_CASE_ENDING)))
		{
		printf("Character \'%c\' is a CONSONANT character!\n", ac_ch);
		}

		else if ((ac_ch_value >= CHAR_DIGIT_BEGINNING) && (ac_ch_value <= CHAR_DIGIT_ENDING))
		{
		printf("Character \'%c\' is a DIGIT character!\n", ac_ch);
		}
		
		else
		{
		printf("Character \'%c\' is a SPECIAL character!\n", ac_ch);
		}
	}

	return (0);
}
