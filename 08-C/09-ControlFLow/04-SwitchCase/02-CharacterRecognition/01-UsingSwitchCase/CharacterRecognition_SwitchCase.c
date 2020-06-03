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
	printf("Enter a character : ");
	ac_ch = getch();
	printf("\n\n");
	switch (ac_ch)
	{
	case 'A':
	case 'a':
	case 'E':
	case 'e':
	case 'I':
	case 'i':
	case 'O':
	case 'o':
	case 'U':
	case 'u':
	printf("Character \'%c\' is a VOWEL character!\n", ac_ch);
	break;
	
	default:
	ac_ch_value = (int)ac_ch;
	
	//If value is between (65 AND 90) OR (97 AND 122), it is an Alphabet, but it is A 'CONSONANT'
	if (((ac_ch_value  >= CHAR_ALPHABET_UPPER_CASE_BEGINNING) &&
		 (ac_ch_value  <= CHAR_ALPHABET_UPPER_CASE_ENDING)) ||
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
	
	break; // default's break
	}//switch case
	
	printf("Switch Case Block Complete!\n");

	return (0);
}
