#include <stdio.h>

int main(void)
{
	// variable declarations
	int ac_a = 5;
	
	//function prototypes
	void ac_change_count(void);

	//code
	printf("\n");
	printf("Local variable in main() A = %d\n", ac_a);

	ac_change_count();
	
	ac_change_count();
	
	// Since, 'local_count' is a local static variable of change_count(), 
	// it WILL retain its value from previous call to change_count().
	
	ac_change_count();

	return(0);
}

void ac_change_count(void)
{
	// variable declarations
	// 'local_count' is a Local Static Variable. It is local to change_count() only.
	// It will retain its value between calls to change_count()
	
	static int ac_local_count = 0;
	
	//code
	ac_local_count = ac_local_count + 1;
	
	printf("static Local variable in change_count()  = %d\n", ac_local_count);

}
