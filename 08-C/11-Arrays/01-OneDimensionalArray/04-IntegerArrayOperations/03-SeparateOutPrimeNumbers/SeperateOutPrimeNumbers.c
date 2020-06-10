#include<stdio.h>

#define AC_ARRAY_SIZE 10

int main()
{
	//declarations
	int ac_i ,ac_j, ac_count=0;
	int i_ac_array[AC_ARRAY_SIZE];
	
	//code
	printf("\n\n");
	printf("Enter %d elements for array:\n", AC_ARRAY_SIZE);
	
	for(ac_i=0; ac_i < AC_ARRAY_SIZE; ac_i++)
		scanf("%d",&i_ac_array[ac_i]);
	
	printf("\n\n");
	printf("Printing Array: ");
	
	for(ac_i=0; ac_i < AC_ARRAY_SIZE; ac_i++)
		printf("%d  ",i_ac_array[ac_i]);
	
	printf("\n\n");
	printf("Prime numbers from array: ");
	for(ac_i=0; ac_i < AC_ARRAY_SIZE; ac_i++)
	{
		ac_count=0;
		for(ac_j=1; ac_j <=i_ac_array[ac_i]; ac_j++ )
		{
			if(i_ac_array[ac_i] % ac_j== 0)
				ac_count ++;
		}
		if(ac_count==2)
			printf("%d  ",i_ac_array[ac_i]);
	}
	printf("\n");
	
	return 0;

}
