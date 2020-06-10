#include <stdio.h> 

int main(void)
{
	//function prototypes
	void ac_display_information(void);
	void Ac_Function_Country(void);

	//code
	ac_display_information(); //function call
	Ac_Function_Country(); //function call
	
	return(0);

}

// ****** User-Defined Functions' Definitions... ***
void ac_display_information(void) //function definition
{
	//function prototypes
	void Ac_Function_My(void);
	void Ac_Function_Name(void);
	void Ac_Function_Is(void);
	void Ac_Function_FirstName(void);
	void Ac_Function_MiddleName(void);
	void Ac_Function_Surname(void);
	void Ac_Function_OfAMC(void);

	//code
	// *** FUNCTION CALLS ***
	Ac_Function_My();
	Ac_Function_Name();
	Ac_Function_Is();
	Ac_Function_FirstName();
	Ac_Function_MiddleName();
	Ac_Function_Surname();
	Ac_Function_OfAMC();

}

void Ac_Function_My(void) //function definition
{
	//code
	printf("\n");
	printf("My");
}

void Ac_Function_Name(void) //function definition
{
	//code
	printf("\n");
	printf("Name");

}

void Ac_Function_Is(void) //function definition
{
	//code
	printf("\n");
	printf("Is");

}

void Ac_Function_FirstName(void) //function definition
{
	//code
	printf("\n");
	printf("Akshay");
	
}

void Ac_Function_MiddleName(void) //function definition
{
	//code
	printf("\n");
	printf("Ramesh");

}

void Ac_Function_Surname(void) //function definition
{
	//code
	printf("\n");
	printf("Chandawale");

}

void Ac_Function_OfAMC(void) //function definition
{
	//code
	printf("\n");
	printf("Of ASTROMEDICOMP");

}

void Ac_Function_Country(void) //function definition
{
	//code
	printf("\n");
	printf("I live In India.");
	printf("\n");

}

