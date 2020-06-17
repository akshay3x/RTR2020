#include <stdio.h>

struct MyPoint
{
	int x;
	int y;
};

struct MyPointProperties
{
	int quadrant;
	char axis_location[20];
};

struct MyPoint point;
struct MyPointProperties point_properties;

int main(void)
{
	//code
	printf("\n\n");
	printf("Enter X coordinate for point A:");
	scanf("%d", &point.x);

	printf("Enter Y coordinate for point A:");
	scanf("%d", &point.y);

	printf("\n");
	printf("Coordinates of point: Point(%d, %d)\n", point.x, point.y);

	printf("\n");
	
	if(point.x == 0 && point.y == 0)
		printf("Point is Origin x(%d, %d)", point.x, point.x);

	else
	{
		if(point.x == 0)
		{
			if(point.y < 0)
				strcpy(point_properties.axis_location, "Negative Y Axis");
			if(point.y > 0)
				strcpy(point_properties.axis_location, "Positive Y Axis");
			
			printf("Point lies on %s \n", point_properties.axis_location);
		}

		else if(point.y == 0)
		{
			if(point.x < 0)
				strcpy(point_properties.axis_location, "Negative X Axis");
			if(point.x > 0)
				strcpy(point_properties.axis_location, "Positive X Axis");
			
			printf("Point lies on %s \n", point_properties.axis_location);
		}

		else
		{
			if(point.x > 0 && point.y > 0)
				point_properties.quadrant = 1;
			
			else if(point.x < 0 && point.y > 0)
				point_properties.quadrant = 2;
			
			else if(point.x < 0 && point.y < 0)
				point_properties.quadrant = 3;
			
			else
				point_properties.quadrant = 4;
			

			point_properties.axis_location[0] = '\0';
		
		printf("Point lies in quadrant %d\n", point_properties.quadrant);
		}
	}

	return (0);
}
