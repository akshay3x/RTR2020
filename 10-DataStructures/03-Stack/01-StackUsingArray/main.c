#include<stdio.h>

#define STACK_SIZE 10

struct Stack
{
	int array[STACK_SIZE];
	int top;
};
	
struct Stack MyStack;

int menu(void);
void push(int);
void pop(void);
void display(void);

void main()
{
	//variable declarations
	int iOption, number;

	//code
	MyStack.top = -1;

	while(1)
	{
		iOption = menu();

		if(iOption == 4)
		{
			printf("\n");
			printf("EXITING...!\n");
			exit(0);
		}

		switch(iOption)
		{
			case 1:
				printf("\n");
				printf("ENTER THE DATA: ");
				scanf("%d", &number);

				push(number);
				break;

			case 2:
				pop();
				break;

			case 3:
				display();
				break;

			default:
				break;
		}
	}

	return;
}

int menu()
{
	//variable declarations
	int iOption;

	//code
	printf(" ----------------\n");
	printf(" [1]. PUSH DATA\n");
	printf(" [2]. POP DATA\n");
	printf(" [3]. DISPLAY STACK\n");
	printf(" [4]. EXIT\n");
	printf(" ----------------\n");

	printf("ENTER YOUR OPTION: ");
	scanf("%d", &iOption);

	return iOption;
}


void push(int data)
{
	//code
	if(MyStack.top == STACK_SIZE - 1)
	{
		printf("\n");
		printf("STACK OVERFLOW...!\n");
		return;
	}

	MyStack.top++;
	MyStack.array[MyStack.top] = data;

	display();
}


void pop()
{
	//code
	if(MyStack.top == -1)
	{
		printf("\n");
		printf("STACK EMPTY...!\n");
		return;
	}

	MyStack.top--;
	display();
}

void display()
{
	//variable declarations
	int i;

	//code
	if(MyStack.top == -1)
	{
		printf("\n");
		printf("STACK EMPTY...!\n");
		return;
	}

	printf("--- STACK ELEMENTS---\n\n");

	printf("top--->");
	for(i = MyStack.top; i >= 0; i--)
		printf("\t%d\n", MyStack.array[i]);

	printf("---------------------\n");
	return;
}
