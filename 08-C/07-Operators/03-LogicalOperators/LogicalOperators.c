#include <stdio.h>
int main(void)
{
	//variable declarations
	int ac_a;
	int ac_b;
	int ac_c;
	int ac_result;

	//code
	printf("Enter 1st Integer (A):");
	scanf("%d", &ac_a);
	
	printf("Enter 2nd Integer (B):");
	scanf("%d", &ac_b);
	
	printf("Enter 3rd Integer (C):");
	scanf("%d", &ac_c);
	printf("\n");
	
	printf("If answer = 0, it is 'FALSE'.\n");
	printf("If answer = 1, it is 'TRUE'. \n\n");

	ac_result = (ac_a <= ac_b) && (ac_b != ac_c);
	printf("-------LOGICAL AND (&&)------- \nAnswer is TRUE (1) If and only if BOTH conditions are TRUE.\nAnswer is FALSE (0), if any one or both conditions are FALSE.\n\n");
	printf("A = %d is less than or equal to B = %d AND B = %d is not equal to C =%d \nAnswer = %d\n", ac_a, ac_b, ac_b, ac_c, ac_result);
	printf("\n");
	
	ac_result = (ac_b >= ac_a) || (ac_a == ac_c);
	printf("-------LOGICAL OR (||)-------- \nAnswer is FALSE (0) If and only if BOTH conditions are FALSE.\nAnswer is TRUE (1), If any one or both conditions are TRUE.\n\n");
	printf("Either B = %d is greater than or equal to A = %d OR A = %d is equal to C = %d \nAnswer = %d\n\n", ac_b, ac_a, ac_a, ac_c, ac_result);
	
	
	printf("-------LOGICAL NOT (!)--------\n"); 
	ac_result = !ac_a;
	printf("A = %d and using logical NOT (!) operator on A gives result = %d\n", ac_a, ac_result);
	
	ac_result = !ac_b;
	printf("B = %d and using logical NOT (!) operator on B gives result = %d\n", ac_b, ac_result);
	
	ac_result = !ac_c;
	printf("C = %d and using logical NOT (!) operator on C gives result = %d\n\n", ac_c, ac_result);
	
	printf("\n");

	ac_result = (!(ac_a <= ac_b) && !(ac_b != ac_c));
	printf("Using logical NOT (!) on (A <= B) and also on (B != C) and then ANDing them afterwards gives \nresult = %d\n", ac_result);
	printf("\n");

	ac_result = !((ac_b >= ac_a) || (ac_a == ac_c));
	printf("Using logical NOT (!) on entire logical expression (B >= A) || (B ==A) gives \nresult = %d\n", ac_result);
	printf("\n");

	ac_result = (!(ac_a <= ac_b) && !(ac_b != ac_c));
	printf("Using logical NOT (!) on (A <= B) and also on (B != C) and then ANDing them afterwards gives \nresult = %d\n", ac_result);
	printf("\n");

	ac_result = !((ac_b >= ac_a) || (ac_a == ac_c));
	printf("Using logical NOT (!) on entire logical expression (B >= A) || (A == C) gives \nresult = %d\n", ac_result);
	printf("\n");
	
	return(0);
}