#include <stdio.h>
#include <math.h>

int main(void)
{
	//structure declarations
	struct AC_MyPoint
	{
		int ix;
		int iy;
	};

	struct AC_MyLine
	{
		struct AC_MyPoint point_P1;
		struct AC_MyPoint point_P2;
	};

	//variable declarations
	struct AC_MyLine line_L1;
	int xdiff = 0;
	int ydiff = 0;
	float length_of_line = 0;

	//code 
	printf("\n");
	printf("Enter Coordinates for P1:\n");
	printf("X= ");
	scanf("%d", &line_L1.point_P1.ix);

	printf("\n");
	printf("Y= ");
	scanf("%d", &line_L1.point_P1.iy);

	printf("\n");
	printf("Enter Coordinates for P2:\n");
	printf("X= ");
	scanf("%d", &line_L1.point_P2.ix);

	printf("\n");
	printf("Y= ");
	scanf("%d", &line_L1.point_P2.iy);

	xdiff = line_L1.point_P1.ix - line_L1.point_P2.ix;
	ydiff = line_L1.point_P1.iy - line_L1.point_P2.iy;

	if(xdiff < 0)
		xdiff = xdiff * -1;

	if(ydiff < 0)
		ydiff = ydiff * -1;

	length_of_line = sqrtf((xdiff * xdiff) + (ydiff * ydiff));

	printf("\n");
	printf("Point P1: P1(%d, %d)\n", line_L1.point_P1.ix, line_L1.point_P1.iy);
	printf("Point P2: P2(%d, %d)\n", line_L1.point_P2.ix, line_L1.point_P2.iy);

	printf("\n");
	printf("Length of Line between P1 and P2 = %f\n", length_of_line);

	return (0);
}
