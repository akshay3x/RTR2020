#include <stdio.h>
int main(void)
{
	//variable declarations
	int ac_a, ac_b;
	int ac_p, ac_q;
	char ac_ch_result_01, ac_ch_result_02;
	int ac_i_result_01, ac_i_result_02;
	
	//code
	ac_a = 7;
	ac_b = 5;
	
	ac_ch_result_01 = (ac_a > ac_b) ? 'A' : 'B';
	ac_i_result_01 = (ac_a > ac_b) ? ac_a : ac_b;
	printf("Ternary Operator Answer 1: (%d > %d) ? ( A : B) -> %c and %d.\n", ac_a, ac_b, ac_ch_result_01, ac_i_result_01);
	
	ac_p = 30;
	ac_q = 31;
	
	ac_ch_result_02 = (ac_p != ac_q) ? 'P' : 'Q';
	ac_i_result_02 = (ac_p != ac_q) ? ac_p : ac_q;
	printf("Ternary Operator Answer 2: (%d != %d ) ? ( P : Q ) -> %c and %d.\n", ac_p, ac_q, ac_ch_result_02, ac_i_result_02);
	printf("\n");
	
	return(0);
}