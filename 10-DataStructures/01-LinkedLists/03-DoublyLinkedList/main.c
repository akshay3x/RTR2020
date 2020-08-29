#include<stdio.h>

//Defining Structure
struct Node
{
	int data;
	struct Node *next;
	struct Node *prev;
};

//Front pointer for tracking the List
struct Node *Front = NULL;

//Function Declarations
void CreateNode(struct Node **);
void CreateLinkedList(void);

void AddAtFront();
void AddAtEnd();
void AddAfter(void);
void AddBefore(void);

void DeleteFromFront();
void DeleteFromEnd();
void DeleteNode(void);
void DeleteLinkedList(void);

void DisplayLinkedList(void);


//main()
int main(void)
{
	//local variables
	int iOption;

	//code
	for(;;)
	{
		printf("\n");
		printf(" ----------------------\n");
		printf(" [ 1]. CREATE LINKED LIST\n");
		printf(" [ 2]. ADD ELEMENT AT FRONT\n");
		printf(" [ 3]. ADD ELEMENT AT END\n");
		printf(" [ 4]. ADD AFTER\n");
		printf(" [ 5]. ADD BEFORE\n");
		printf(" [ 6]. DELETE ELEMENT FROM FRONT\n");
		printf(" [ 7]. DELETE ELEMENT FROM END\n");
		printf(" [ 8]. DELETE NODE WITH VALUE\n");
		printf(" [ 9]. DELETE ENTIRE LIST\n");
		printf(" [10]. DISPLAY\n");
		printf(" [11]. EXIT\n");
		printf(" ----------------------\n");
		printf("  ENTER OPTION NUMBER: ");
		scanf("%d", &iOption);

		switch(iOption)
		{
			case 1:
				CreateLinkedList();
				break;

			case 2:
				AddAtFront();
				break;

			case 3:
				AddAtEnd();
				break;

			case 4:
				AddAfter();
				break;

			case 5:
				AddBefore();
				break;

			case 6:
				DeleteFromFront();
				break;

			case 7:
				DeleteFromEnd();
				break;

			case 8:
				DeleteNode();
				break;

			case 9:
				DeleteLinkedList();
				break;

			case 10:
				DisplayLinkedList();
				break;

			case 11:
				DeleteLinkedList();
				printf("  EXITING...!\n");
				exit(0);
				
			default:
				break;
		}
	}
	return 0;
}


void CreateLinkedList(void)
{
	//local variables
	int NumElements = 0;

	//code
	if(Front != NULL)
		printf("  LIST IS ALREADY CREATED\n");
	else
	{
		printf("\n ENTER NUMBER OF ELEMENTS FOR LIST: ");
		scanf("%d", &NumElements);

		while (NumElements)
		{
			AddAtEnd();
			NumElements--;
		}
	}
}


void CreateNode(struct Node **node)
{
	//local variables
	*node = (struct Node*) malloc(sizeof(struct Node));

	//code
	if(*node == NULL)
	{
		printf(" MEMORY ALLOCATION FAILED: CREATENODE()\n");
		printf(" EXITING...\n");
		exit(0);
	}

	printf("  ENTER INTEGER DATA FOR NODE: ");
	scanf("%d", &(*node)->data);

	(*node)->next = NULL;
	(*node)->prev = NULL;
}


void AddAtFront()
{
	//local varables
	struct Node *node = NULL;
	struct Node *temp = NULL;

	//code
	CreateNode(&node);

	if(Front == NULL)
		Front = node;
	else
	{
		temp = Front;
		node->next = temp;
		temp->prev = node;
		Front = node;
	}
	DisplayLinkedList();
}


void AddAtEnd()
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
		node->prev = traverse_node;
	}
	DisplayLinkedList();
}

void AddAfter()
{
	struct Node *node = NULL;
	struct Node *traverse_node = NULL;
	struct Node *temp = NULL;
	int num;

	if(Front == NULL)
		return;

	printf("  ENTER NUMBER AFTER YOU WANT TO INSERT: ");
	scanf("%d", &num);

	traverse_node = Front;
	while((traverse_node != NULL) && (traverse_node->data != num))
	{
		temp = traverse_node;
		traverse_node = traverse_node->next;
	}

	if(traverse_node == NULL)
	{
		printf("NUMBER NOT IN LIST\n");
		return;
	}

	CreateNode(&node);

	node->next = traverse_node->next;
	node->prev = traverse_node;

	traverse_node->next = node;

	DisplayLinkedList();
}

void AddBefore()
{
	struct Node *node = NULL;
	struct Node *traverse_node = NULL;
	struct Node *temp = NULL;
	int num;

	if(Front == NULL)
		return;

	printf("  ENTER NUMBER BEFORE YOU WANT TO INSERT: ");
	scanf("%d", &num);

	traverse_node = Front;
	while((traverse_node != NULL) && (traverse_node->data != num))
	{
		temp = traverse_node;
		traverse_node = traverse_node->next;		
	}

	if(traverse_node == NULL)
	{
		printf("  NUMBER NOT IN LIST\n");
		return;
	}

	CreateNode(&node);

	if(Front->data == num)
	{
		node->next = Front;
		Front->prev = node;
		Front = node;
	}
	else
	{
		node->next = traverse_node;
		traverse_node->prev = node;
		temp->next = node;
		node->prev = temp;
	}

	DisplayLinkedList();
}

void DeleteFromFront()
{
	//local varables
	struct Node *node = NULL;

	//code
	if(Front == NULL)
	{
		printf("\n");
		printf("  NO ELEMENTS IN LIST...!\n");
		return;
	}

	node = Front;
	Front = Front->next;

	if(Front != NULL)
		Front->prev = NULL;

	free(node);
	node = NULL;

	DisplayLinkedList();
}

void DeleteFromEnd()
{
	//local varables
	struct Node *traverse_node = NULL;
	struct Node *temp = NULL;

	//code
	if(Front == NULL)
	{
		printf("  NO ELEMENTS IN LIST...!\n");
		return;
	}
	else
	{
		traverse_node = Front;
		temp = Front;

		while(traverse_node->next != NULL)
		{
			temp = traverse_node;
			traverse_node = traverse_node->next;
		}

		if(traverse_node == Front)
			Front = NULL;

		temp->next = NULL;
		traverse_node->prev = NULL;
		
		free(traverse_node);
	}

	DisplayLinkedList();
}

void DeleteNode()
{
	int number;
	struct Node *traverse_node = NULL;
	struct Node *temp = NULL;
	int flag = 0;

	if(Front == NULL)
		return;

	printf("  ENTER VALUE FOR DELETING NODE: ");
	scanf("%d", &number);

	if (Front->data == number)
	{
		temp = Front;
		Front = Front->next;

		if(Front != NULL)
			Front->prev = NULL;

		free(temp);
	}
	else
	{
		traverse_node = Front;
		while((traverse_node != NULL) && (traverse_node->data != number))
		{
			temp = traverse_node;
			traverse_node = traverse_node->next;
		}

		if(traverse_node == NULL)
		{
			printf("  NUMBER NOT IN LIST\n");
			return;
		}

		temp->next = traverse_node->next;
		free(traverse_node);
	}
	DisplayLinkedList();
}



void DeleteLinkedList(void)
{
	//code
	while(Front != NULL)
	{
		DeleteFromEnd();
	}
	Front = NULL;
}

void DisplayLinkedList(void)
{
	//local varables
	struct Node *traverse_node = NULL;

	//code
	if(Front == NULL)
	{
		printf("\n");
		printf("  NO ELEMENTS IN LIST...!\n");
	}
	else
	{
		traverse_node = Front;
		printf("-----------------------\n");
		printf("  LIST\n");
		printf(" ADDRESS\t PREV\t\tDATA\t LINK\n");

		while(traverse_node != NULL)
		{
			printf(" %p\t", traverse_node);
			printf("[%p <---- ",traverse_node->prev);
			printf("%d ----> ", traverse_node->data);
			printf("%p]\n",traverse_node->next);
			traverse_node = traverse_node->next;
		}
		printf("-----------------------\n");
	}
}
