#include<stdio.h>

//macro definitions
#define QUEUE_SIZE 6

//global variables
int queue[QUEUE_SIZE];

long QFront, QRear;

//global function declarations
void Enqueue(void);
void Dequeue(void);
void Display(void);

//main()
int main()
{
	//variable Declarations
	int iOption;

	//code
	QFront = QRear = -1;

	while(1)
	{
		printf("\n\n");
		printf(" -----------\n");
		printf(" 1. ENQUEUE\n");
		printf(" 2. DEQUEUE\n");
		printf(" 3. DISPLAY\n");
		printf(" 4. EXIT\n");
		printf(" -----------\n");
		printf(" Enter Option: ");
		scanf("%d", &iOption);

		switch(iOption)
		{
			case 1:
				Enqueue();
				break;

			case 2:
				Dequeue();
				break;

			case 3:
				Display();
				break;

			case 4:
			while(QRear != -1)
				Dequeue();
				exit(0);

			default :
				break;
		}
	}

	return 0;
}

void Enqueue(void)
{
	//local variables
	int number;

	//code
	if( QRear < QUEUE_SIZE-1)
	{
		printf(" ENTER A NUMBER TO ENQUEUE: ");
		scanf("%d", &number);
		
		if(QFront == -1)
		{
			QFront = 0;
			QRear = 0;
		}

		else
			QRear++;
		
		queue[QRear] = number;
	}
	else
	{
		printf("\n");
		printf(" QUEUE SIZE: %d \n QUEUE IS FULL...!\n", QUEUE_SIZE);
		return;
	}
	Display();
}

void Dequeue(void) 
{
	//local variables
	int number;
	int i;

	//code
	if(QFront != -1)
	{
		number = queue[QFront];

		if(QFront == QRear)
		{
			QFront = -1;
			QRear = -1;
		}

		else
		{

			//adjusting queue elements in array
			for (i = 0; i < QRear; i++)
				queue[i] = queue[i + 1];
			QRear--;
		}
		printf("\n");
		printf(" NUMBER DELETED: %d...!\n", number);

	}
	else
	{
		printf("\n");
		printf("QUEUE IS EMPTY...!\n");
		return;
	}

	Display();
}


void Display(void)
{
	//local variables
	int i;

	//code
	if(QFront == -1)
	{
		printf("\n");
		printf(" QUEUE IS EMPTY...!\n");
		return;
	}

	printf("----QUEUE----\n\t");
	for(i = QFront; i <= QRear; i++)
		printf("[%d] %d\n\t", i + 1, queue[i]);
	printf("\n");
}
