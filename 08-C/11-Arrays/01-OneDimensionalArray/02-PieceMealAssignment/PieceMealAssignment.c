#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArrayOne[10];
	int iArrayTwo[10];

	//code
	// ****** iArrayOne[] ******
	iArrayOne[0] = 4;
	iArrayOne[1] = 8;
	iArrayOne[2] = 12;
	iArrayOne[3] = 16;
	iArrayOne[4] = 20;
	iArrayOne[5] = 24;
	iArrayOne[6] = 28;
	iArrayOne[7] = 32;
	iArrayOne[8] = 36;
	iArrayOne[9] = 40;

	printf("\n\n");

	printf("Piece-meal (Hard-coded) Assignment 'iArrayOne[]':\n");
	printf("1st Element Of Array iArrayOne[] = %d\n", iArrayOne[0]);
	printf("2nd Element Of Array iArrayOne[] = %d\n", iArrayOne[1]);
	printf("3rd Element Of Array iArrayOne[] = %d\n", iArrayOne[2]);
	printf("4th Element Of Array iArrayOne[] = %d\n", iArrayOne[3]);
	printf("5th Element Of Array iArrayOne[] = %d\n", iArrayOne[4]);
	printf("6th Element Of Array iArrayOne[] = %d\n", iArrayOne[5]);
	printf("7th Element Of Array iArrayOne[] = %d\n", iArrayOne[6]);
	printf("8th Element Of Array iArrayOne[] = %d\n", iArrayOne[7]);
	printf("9th Element Of Array iArrayOne[] = %d\n", iArrayOne[8]);
	printf("10th Element Of Array iArrayOne[]= %d\n", iArrayOne[9]);

// ****** iArrayTwo[] ******
	printf("\n\n");
	printf("Enter 1st Element fo iArrayTwo[]' : ");
	scanf("%d", &iArrayTwo[0]);  
 
	printf("Enter 2nd Element Of iArrayTwo[]' : ");
	scanf("%d", &iArrayTwo[1]);

	printf("Enter 3rd Element Of iArrayTwo[]' : ");
	scanf("%d", &iArrayTwo[2]);

	printf("Enter 4th Element Of iArrayTwo[]' : ");
	scanf("%d", &iArrayTwo[3]);

	printf("Enter 5th Element Of iArrayTwo[]' : ");
	scanf("%d", &iArrayTwo[4]);

	printf("Enter 6th Element Of iArrayTwo[]' : ");
	scanf("%d", &iArrayTwo[5]);

	printf("Enter 7th Element Of iArrayTwo[]' : ");
	scanf("%d", &iArrayTwo[6]);

	printf("Enter 8th Element Of iArrayTwo[]' : ");
	scanf("%d", &iArrayTwo[7]);

	printf("Enter 9th Element Of iArrayTwo[]' : ");
	scanf("%d", &iArrayTwo[8]);

	printf("Enter 10th Element Of iArrayTwo[]': ");
	scanf("%d", &iArrayTwo[9]);

	printf("\n\n");

	printf("Piece-meal (User Input) Assignment Array:\n");

	printf("1st Element Of Array iArrayTwo[] = %d\n", iArrayTwo[0]);

	printf("2nd Element Of Array iArrayTwo[] = %d\n", iArrayTwo[1]);
	
	printf("3rd Element Of Array iArrayTwo[] = %d\n", iArrayTwo[2]);

	printf("4th Element Of Array iArrayTwo[] = %d\n", iArrayTwo[3]);

	printf("5th Element Of Array iArrayTwo[] = %d\n", iArrayTwo[4]);

	printf("6th Element Of Array iArrayTwo[] = %d\n", iArrayTwo[5]);

	printf("7th Element Of Array iArrayTwo[] = %d\n", iArrayTwo[6]);

	printf("8th Element Of Array iArrayTwo[] = %d\n", iArrayTwo[7]);

	printf("9th Element Of Array iArrayTwo[] = %d\n", iArrayTwo[8]);

	printf("10th Element Of Array iArrayTwo[] = %d\n\n", iArrayTwo[9]);

return(0);
}
