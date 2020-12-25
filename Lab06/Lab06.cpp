#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _list list;
typedef list* positision;

struct  _list
{
	int number;
	positision next;
};

int getRandomNumber();
positision makeElement(int);

void pushInStack(positision);
int popStack(positision);


void pushQueue(positision);
int popQueque(positision);

void printList(positision);

void printMenu(void);
void deleteAll(positision);


int	main(int argc, char** argv)
{

	list stack;
	list queue;

	int userSelect = 0;

	stack.next = NULL;
	queue.next = NULL;

	int randomNumber = 0;
	srand((unsigned)time(NULL));


	while (userSelect != -1)
	{
		printMenu();
		scanf(" %d", &userSelect);

		switch (userSelect)
		{
		case 1:
			pushInStack(&stack);
			break;
		case 2:
			popStack(&stack);
			break;
		case 3:
			printList(stack.next);
			break;
		case 4:
			pushQueue(&queue);
			break;
		case 5:
			popQueque(&queue);
			break;
		case 6:
			printList(queue.next);
			break;
		case -1:
			printf("Dovdenja!\n");
			break;
		default:
			printf("Nepoznata operacija!\n");
			break;
		}
	}

	deleteAll(&queue);
	deleteAll(&stack);

	printf("Dovidenja nakon dealokacije\n");
	return 0;
}

int getRandomNumber(void)
{
	int randomNumber = (rand() % (100 - 10 + 1)) + 10;

	return randomNumber;
}

positision makeElement(int number)
{
	positision newElement = (positision)malloc(sizeof(list));

	newElement->number = number;
	newElement->next = NULL;
	return newElement;
}

void pushInStack(positision head)
{
	positision temp;
	int value = getRandomNumber();
	temp = makeElement(value);

	temp->next = head->next;
	head->next = temp;

	printf("dodan broj %d\n", value);
}

int popStack(positision head)
{
	positision temp = head->next;
	int popValue = -1;

	popValue = temp->number;
	head->next = temp->next;
	free(temp);
	printf("Pop stack number %d\n", popValue);
	return popValue;
}

void printList(positision head)
{
	while (head != NULL)
	{
		printf("%d\t", head->number);
		head = head->next;
	}
}

void pushQueue(positision head)
{
	int pushNumber = getRandomNumber();
	positision temp = makeElement(pushNumber);


	while (head->next != NULL)
	{
		head = head->next;
	}

	temp->next = head->next;
	head->next = temp;
	printf("dodan broj %d\n", pushNumber);


}

int popQueque(positision head)
{
	positision temp;
	int popedValue = -1;

	temp = head->next;
	head->next = temp->next;
	popedValue = temp->number;
	printf("\npoped from queqe: %d\n", popedValue);
	free(temp);
	return popedValue;
}

void printMenu(void)
{
	printf("###################################\n");
	printf("# Push to stack ********** %d #\n", 1);
	printf("# Pop from stack ********* %d #\n", 2);
	printf("# Print stack ************ %d #\n", 3);
	printf("# Push to queue ********** %d #\n", 4);
	printf("# Pop from queue ********* %d #\n", 5);
	printf("# Print queue ************ %d #\n", 6);
	printf("# Close the application ** %d #\n", -1);
	printf("###################################\n\n");

	printf("Enter your command:\t");
}

void deleteAll(positision head)
{
	positision temp = head->next;

	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
}
