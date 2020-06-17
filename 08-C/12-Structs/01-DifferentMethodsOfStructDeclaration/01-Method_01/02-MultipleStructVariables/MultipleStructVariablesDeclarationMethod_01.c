#include <stdio.h>

struct MyPoint
{
	int x;
	int y;
} point_A, point_B, point_C, point_D, point_E;

int main(void)
{
	//code
	point_A.x = 2;
	point_A.y = 3;

	point_B.x = 4;
	point_B.y = 6;

	point_C.x = 6;
	point_C.y = 9;

	point_D.x = 8;
	point_D.y = 12;

	point_E.x = 10;
	point_E.y = 15;

	printf("\n");
	printf("Coordinates of Point A: X = %d\t Y = %d\n", point_A.x, point_A.y);
	printf("Coordinates of Point B: X = %d\t Y = %d\n", point_B.x, point_B.y);
	printf("Coordinates of Point C: X = %d\t Y = %d\n", point_C.x, point_C.y);
	printf("Coordinates of Point D: X = %d\t Y = %d\n", point_D.x, point_D.y);
	printf("Coordinates of Point E: X = %d\t Y = %d\n", point_E.x, point_E.y);

	return (0);
}
