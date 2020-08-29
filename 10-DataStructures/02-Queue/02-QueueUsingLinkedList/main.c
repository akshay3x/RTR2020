#include<stdio.h>

//Defining Structure
struct Node
{
	int data;
	struct Node *next;
};

//Front pointer for tracking the List
struct Node *Front = NULL;

//global function declarations
void Enqueue(void);
void Dequeue(void);
void DisplayQueue(void);

//main()
int main()
{
	//variable Declarations
	int iOption;

	//code
	while(1)
	{
		printf("\n\n");
		printf(" -----------\n");
		printf(" [1]. ENQUEUE\n");
		printf(" [2]. DEQUEUE\n");
		printf(" [3]. DISPLAY\n");
		printf(" [4]. EXIT\n");
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
				DisplayQueue();
				break;

			case 4:
			while(Front != NULL)
				Dequeue();
				exit(0);

			default :
				break;
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
		printf("EXITING...\n");
		exit(0);
	}

	printf("\n ENTER INTEGER DATA TO ENQUEUE: ");
	scanf("%d", &(*node)->data);

	(*node)->next = NULL;
}


void Enqueue(void)
{
	//local varables
	struct Node *node = NULL;
	struct Node *traverse_node = NULL;

	//code
	CreateNode(&node);

	if(Front == NULL)
		Front = node;
	else
	{
		traverse_node = Front;
		while(traverse_node->next != NULL)
		{
			traverse_node = traverse_node->next;
		}
		traverse_node->next = node;
	}
	DisplayQueue();
}

void Dequeue(void) 
{
	//local varables
	struct Node *Delete_node = NULL;

	//code
	if(Front == NULL)
	{
		printf(" QUEUE EMPTY...!\n");
		return;
	}
	
	Delete_node = Front;

	Front = Delete_node->next;
	Delete_node->next = NULL;

	free(Delete_node);
	Delete_node = NULL;

	DisplayQueue();
}


void DisplayQueue(void)
{
	//local varables
	struct Node *traverse_node = NULL;

	//code
	if(Front == NULL)
	{
		printf("\n");
		printf(" QUEUE EMPTY...!\n");
		return;
	}
	else
	{
		traverse_node = Front;

		printf("-----------------------\n");
		printf("QUEUE:\n");
		printf(" ADDRESS \t DATA \t  LINK\n");

		while(traverse_node != NULL)
		{
			printf(" %p\t", traverse_node);
			printf(" [%d---->", traverse_node->data);
			printf(" %p]\n",traverse_node->next);
			traverse_node = traverse_node->next;
		}

		printf("\n");
		printf("-----------------------\n");
	}
}
