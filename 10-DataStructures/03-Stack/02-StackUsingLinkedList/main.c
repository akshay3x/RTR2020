#include<stdio.h>
#include<stdlib.h>

void push();
void pop();
void DisplayStack();

struct Node
{
	int data;
	struct Node *next;
};

struct Node *TOP = NULL;

int main()
{
	int iOption;

	while(1)
	{
		printf("-------------\n");
		printf(" 1.PUSH\n");
		printf(" 2.POP\n");
		printf(" 3.DISPLAY\n");
		printf(" 4.EXIT\n");
		printf("-------------\n");

		printf(" ENTER YOUR CHOICE: ");
		scanf("%d", &iOption);

		switch(iOption)
		{
			case 1:
				push();
				break;
			
			case 2:
				pop();
				break;
				
			case 3:
				DisplayStack();
				break;
				
			case 4:
				while(TOP != NULL)
					pop();
				exit(0);
			
		}
	}
	return 0;
}

void CreateNode(struct Node **node)
{
	//local variables
	*node = (struct Node*) malloc(sizeof(struct Node));

	//code
	if(*node == NULL)
	{
		printf("MEMORY ALLOCATION FAILED:CREATENODE()\n");
		printf("Exiting...\n");
		exit(0);
	}

	printf("\n ENTER INTEGER DATA FOR NODE: ");
	scanf("%d", &(*node)->data);

	(*node)->next = NULL;
}


void push()
{
	//local varables
	struct Node *node = NULL;
	struct Node *temp = NULL;

	//code
	CreateNode(&node);

	if(TOP == NULL)
		TOP = node;
	else
	{
		temp = TOP;
		node->next = temp;
		TOP = node;
	}
	DisplayStack();
}


void pop()
{
	//local varables
	struct Node *pop_node = NULL;

	//code
	if(TOP == NULL)
	{
		printf("STACK EMPTY...!\n");
		return;
	}

	pop_node = TOP;

	TOP = pop_node->next;
	pop_node->next = NULL;

	free(pop_node);
	pop_node = NULL;

	DisplayStack();
}
void DisplayStack(void)
{
	//local varables
	struct Node *traverse_node = NULL;

	//code
	if(TOP == NULL)
	{
		printf("\n");
		printf(" STACK EMPTY...!\n");
	}
	else
	{
		traverse_node = TOP;
		printf("-----------------------\n");
		printf("STACK:\n");
		printf("\t ADDRESS  \tDATA\tNEXT:\n");
		printf("TOP-->");
		while(traverse_node != NULL)
		{
			printf("\t %p\t", traverse_node);
			printf("[%d---->", traverse_node->data);
			printf("%p]\n",traverse_node->next);
			traverse_node = traverse_node->next;
		}
		printf("\n");
		printf("-----------------------\n");
	}
}
