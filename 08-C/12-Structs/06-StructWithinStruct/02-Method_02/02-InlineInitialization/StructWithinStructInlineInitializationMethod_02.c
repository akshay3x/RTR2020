#include <stdio.h>
#include <math.h>

//structure definitions
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

int main(void)
{
	//variable declarations
	struct AC_MyLine line_L1 = {{-10, 5}, {-5, 10}};
	int xdiff = 0;
	int ydiff = 0;
	float length_of_line = 0;

	//code
	xdiff = line_L1.point_P1.ix - line_L1.point_P2.ix;
	ydiff = line_L1.point_P1.iy - line_L1.point_P2.iy;

	if(xdiff < 0)
		xdiff = xdiff * -1;

	if(ydiff < 0)
		ydiff = ydiff * -1;

	//length = square root of [(x1 - x2)2 +(y1 - y2)2]
	length_of_line = sqrtf((xdiff * xdiff) + (ydiff * ydiff));

	printf("\n");
	printf("Point P1: P1(%d, %d)\n", line_L1.point_P1.ix, line_L1.point_P1.iy);
	printf("Point P2: P2(%d, %d)\n", line_L1.point_P2.ix, line_L1.point_P2.iy);

	printf("\n");
	printf("Length of Line between P1 and P2 = %f\n", length_of_line);

	return (0);
}
