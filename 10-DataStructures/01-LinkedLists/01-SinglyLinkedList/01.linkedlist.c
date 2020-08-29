#include<stdio.h>

//Defining Structure
struct Node
{
	int data;
	struct Node *link;
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
				printf("  EXITING...!\n\n");
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

	(*node)->link = NULL;
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
		node->link = temp;
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
		while(traverse_node->link != NULL)
		{
			traverse_node = traverse_node->link;
		}
		traverse_node->link = node;
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
	
	printf(" ENTER NUMBER AFTER YOU WANT TO INSERT: ");
	scanf("%d", &num);
		
	traverse_node = Front;
	while((traverse_node != NULL) && (traverse_node->data != num))
	{
			temp = traverse_node;
			traverse_node = traverse_node->link;
			
	}
		
	if(traverse_node == NULL)
	{
				printf("  NUMBER NOT IN LIST\n");
				return;
	}
		
	CreateNode(&node);
	
	node->link = traverse_node->link;
	traverse_node->link = node;
	
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
	
	printf(" ENTER NUMBER BEFORE YOU WANT TO INSERT: ");
	scanf("%d", &num);
	
	
	traverse_node = Front;
	while((traverse_node != NULL) && (traverse_node->data != num))
	{
		temp = traverse_node;
		traverse_node = traverse_node->link;		
	}
		
	if(traverse_node == NULL)
	{
		printf("  NUMBER NOT IN LIST\n");
		return;
	}
	
	CreateNode(&node);
	if(Front->data == num)
	{
		node->link = Front;
		Front = node;
	}
	else
	{
		node->link = traverse_node;
		temp->link = node;
	}
	
	DisplayLinkedList();
}



void DeleteNode()
{
	int num;
	struct Node *traverse_node = NULL;
	struct Node *temp = NULL;
	int flag = 0;

	if(Front == NULL)
		return;

	printf("  ENTER VALUE FOR DELETING NODE: ");
	scanf("%d", &num);

	if (Front->data == num)
	{
		temp = Front;
		Front = Front->link;
		free(temp);
	}
	else
	{
		traverse_node = Front;
		while((traverse_node != NULL) && (traverse_node->data != num))
		{
			temp = traverse_node;
			traverse_node = traverse_node->link;
			
		}
		
		if(traverse_node == NULL)
		{
				printf("  NUMBER NOT IN LIST\n");
				return;
		}
	temp->link = traverse_node->link;
	free(traverse_node);
	}
	DisplayLinkedList();
}

void DeleteFromFront()
{
	//local varables
	struct Node *Delete_node = NULL;

	//code
	if(Front == NULL)
		return;

	Delete_node = Front;

	Front = Delete_node->link;
	Delete_node->link = NULL;

	free(Delete_node);
	Delete_node = NULL;

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
		printf("  NO ELEMENTS IN LIST\n");
		return;
	}
	else
	{
		traverse_node = Front;
		temp = Front;

		while(traverse_node->link != NULL)
		{
			temp = traverse_node;
			traverse_node = traverse_node->link;
		}

		if(traverse_node == Front)
			Front = NULL;

		free(traverse_node);
		temp->link = NULL;
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
		printf("  LIST:\n");
		printf(" ADDRESS  \tDATA\tLINK\n");
		while(traverse_node != NULL)
		{
			printf(" %p\t", traverse_node);
			printf("[%d---->", traverse_node->data);
			printf("%p]\n",traverse_node->link);
			traverse_node = traverse_node->link;
		}
		printf("\n");
		printf("-----------------------\n");
	}
}
