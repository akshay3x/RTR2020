#include<stdio.h>

//Defining Structure
struct Node
{
	int data;
	struct Node *next;
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
void DeleteNodeByValue(void);
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
		printf(" [ 1]. CREATE A LINKED LIST\n");
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
				DeleteNodeByValue();
				break;

			case 9:
				DeleteLinkedList();
				break;

			case 10:
				DisplayLinkedList();
				break;

			case 11:
				DeleteLinkedList();
				printf("  EXITING...!\n\n");
				exit(0);
				
			default:
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

	printf("\n ENTER INTEGER DATA FOR NODE: ");
	scanf("%d", &(*node)->data);

	(*node)->next = NULL;
}


void CreateLinkedList(void)
{
	//local variables
	int NumElements = 0;

	//code
	if(Front != NULL)
		printf("LIST IS ALREADY CREATED\n");
	else
	{
		printf("\nENTER NUMBER OF ELEMENTS FOR LIST: ");
		scanf("%d",&NumElements);

		while (NumElements)
		{
			AddAtEnd();
			NumElements--;
		}
	}
}


void AddAtFront()
{
	//local varables
	struct Node *node = NULL;
	struct Node *temp = NULL;
	struct Node *traverse_node = NULL;
	//code
	CreateNode(&node);

	if(Front == NULL)
	{
		Front = node;
		Front->next = Front;
	}
	else
	{
		traverse_node = Front;
		
		while(traverse_node->next != Front)
				traverse_node = traverse_node->next;
		
		traverse_node->next = node;
		node->next = Front;
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
	{
		Front = node;
		Front->next = Front;
	}
	else
	{
		traverse_node = Front;
		while(traverse_node->next != Front)
			traverse_node = traverse_node->next;

		traverse_node->next = node;
		node->next = Front;
	}
	DisplayLinkedList();
}

void AddAfter()
{
	//local varables
	struct Node *node = NULL;
	struct Node *traverse_node = NULL;
	struct Node *temp = NULL;
	int num;

	//code
	if(Front == NULL)
		return;

	printf(" ENTER NUMBER AFTER YOU WANT TO INSERT: ");
	scanf("%d", &num);

	traverse_node = Front;
	while((traverse_node != NULL) && (traverse_node->data != num))
	{
			temp = traverse_node;
			traverse_node = traverse_node->next;
	}

	if(traverse_node == NULL)
	{
		printf("\n");
		printf("  NUMBER NOT IN LIST\n");
		return;
	}

	CreateNode(&node);

	node->next = traverse_node->next;
	traverse_node->next = node;

	DisplayLinkedList();
}

void AddBefore()
{
	//local variables
	struct Node *node = NULL;
	struct Node *traverse_node = NULL;
	struct Node *temp = NULL;
	int num;

	//code
	if(Front == NULL)
		return;

	printf(" ENTER NUMBER BEFORE YOU WANT TO INSERT: ");
	scanf("%d", &num);

	traverse_node = Front;
	while((traverse_node != NULL) && (traverse_node->data != num))
	{
		temp = traverse_node;
		traverse_node = traverse_node->next;
	}

	if(traverse_node == NULL)
	{
		printf("\n");
		printf("  NUMBER NOT IN LIST\n");
		return;
	}

	CreateNode(&node);

	if(Front->data == num)
	{
		node->next = Front;
		while(traverse_node->next != Front)
			traverse_node = traverse_node->next;

		traverse_node->next = node;
		Front = node;
	}
	else
	{
		node->next = traverse_node;
		temp->next = node;
	}

	DisplayLinkedList();
}



void DeleteNodeByValue()
{
	//local variables declarations
	int num;
	struct Node *traverse_node = NULL;
	struct Node *temp = NULL;
	int flag = 0;

	//code
	if(Front == NULL)
		return;

	printf("\n");
	printf("  ENTER VALUE FOR DELETING NODE: ");
	scanf("%d", &num);

	traverse_node = Front;
	if (Front->data == num)
	{
		while(traverse_node->next != Front)
			traverse_node = traverse_node->next;

		traverse_node->next = Front->next;
		temp = Front;
		Front = Front->next;
		free(temp);
	}
	else
	{
		while((traverse_node->next != Front) && (traverse_node->data != num))
		{
			temp = traverse_node;
			traverse_node = traverse_node->next;
		}

		if(traverse_node->next == Front && (traverse_node->data != num))
		{
			printf("\n");
			printf("  NUMBER NOT IN LIST\n");
			return;
		}
		else
		{
			temp->next = traverse_node->next;
			free(traverse_node);
		}
	}
	DisplayLinkedList();
}

void DeleteFromFront()
{
	//local varables
	struct Node *Delete_node = NULL;
	struct Node *traverse_node = NULL;

	//code
	if(Front == NULL)
	{
		printf("\n");
		printf("  NO ELEMENTS IN LIST\n");
		return;
	}

	Delete_node = Front;
	traverse_node = Front;

	while(traverse_node->next != Front)
		traverse_node = traverse_node->next;

	if(Front == traverse_node)
	{
		free(Front);
		Front = NULL;
	}
	else
	{
		Front = Delete_node->next;
		traverse_node->next = Front;
		Delete_node->next = NULL;

		free(Delete_node);
		Delete_node = NULL;
	}

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
		printf("\n");
		printf("  NO ELEMENTS IN LIST\n");
		return;
	}
	else
	{
		traverse_node = Front;
		temp = Front;

		while(traverse_node->next != Front)
		{
			temp = traverse_node;
			traverse_node = traverse_node->next;
		}

		if(traverse_node == Front)
		{
			Front->next = NULL;
			Front = NULL;
		}
		else
		temp->next = Front;

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
		return;
	}
	else
	{
		traverse_node = Front;

		printf("-----------------------\n");
		printf("  LIST:\n");
		printf(" ADDRESS  \tDATA\tLINK\n");

		do
		{

			printf(" %p\t", traverse_node);
			printf("[%d---->", traverse_node->data);
			printf("%p]\n",traverse_node->next);

			traverse_node = traverse_node->next;
		}while(traverse_node != Front);

		printf("\n");
		printf("-----------------------\n");
	}
}
