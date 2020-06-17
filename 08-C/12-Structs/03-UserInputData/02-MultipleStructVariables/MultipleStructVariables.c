#include <stdio.h>

struct AcMyPoint
{
	int x;
	int y;
};

int main(void)
{
	struct AcMyPoint point_A;
	struct AcMyPoint point_B;
	struct AcMyPoint point_C;
	struct AcMyPoint point_D;
	struct AcMyPoint point_E;

	printf("\n\n");
	printf("Enter Coordinates for Point A\n");
	printf("X = ");
	scanf("%d", &point_A.x);
	printf("Y = ");
	scanf("%d", &point_A.y);

	printf("\n\n");
	printf("Enter Coordinates for Point B\n");
	printf("X = ");
	scanf("%d", &point_B.x);
	printf("Y = ");
	scanf("%d", &point_B.y);

	printf("\n\n");
	printf("Enter Coordinates for Point C\n");
	printf("X = ");
	scanf("%d", &point_C.x);
	printf("Y = ");
	scanf("%d", &point_C.y);

	printf("\n\n");
	printf("Enter Coordinates for Point D\n");
	printf("X = ");
	scanf("%d", &point_D.x);
	printf("Y = ");
	scanf("%d", &point_D.y);

	printf("\n\n");
	printf("Enter Coordinates for Point E\n");
	printf("X = ");
	scanf("%d", &point_E.x);
	printf("Y = ");
	scanf("%d", &point_E.y);

	printf("\n\n");
	printf("Points:\n");
	printf("Point A: A(%d, %d)\n", point_A.x, point_A.y);
	printf("Point B: B(%d, %d)\n", point_B.x, point_B.y);
	printf("Point C: C(%d, %d)\n", point_C.x, point_C.y);
	printf("Point D: D(%d, %d)\n", point_D.x, point_D.y);
	printf("Point E: E(%d, %d)\n", point_E.x, point_E.y);

	return (0);
}