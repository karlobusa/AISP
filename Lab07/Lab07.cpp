#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct _list list;
typedef list* position;
struct _list
{
	int element;
    int priority;
	position next;
};

void printMenu(void);

void stackPush(position, int);
void stackPop(position);

void queuePush(position);

void printList(position);
int getRandomNumber(void);
int getRandomPriority(void);

position makeNewElement(int);
position makeNewWithPriority(int, int);

void dropLast(position);

void deleteAll(position);


int main(int argc, char** argv)
{
	list stack;
	list queue;

	stack.next = NULL;
	queue.next = NULL;

    int userInput = 0;

    int maxStackCapacity = 0;
    int currentStackCapacity = 0;
    int isStackFull = 0;

    srand((unsigned)time(NULL));

    do
    {
        printf("Enter max stack capacity: ");
        scanf(" %d", &maxStackCapacity);
    } while (maxStackCapacity <= 0);


    while (userInput != -1)
    {
        printMenu();
        scanf(" %d", &userInput);


        switch (userInput)
        {
        case 1:
            if (currentStackCapacity == maxStackCapacity)
            {
                isStackFull = 1;
            }
            else {
                currentStackCapacity++;
                isStackFull = 0;
            }
            stackPush(&stack, isStackFull);
            break;
        case 2:
            stackPop(&stack);
            currentStackCapacity--;
            break;
        case 3:
            printList(stack.next);
            break;
        case 4:
            queuePush(&queue);
            break;
        case 5:
            stackPop(&stack);
            break;
        case 6:
            printList(queue.next);
            break;
        case 7:
            deleteAll(&stack);
            deleteAll(&queue);
            break;
        case -1:
            printf("Dovidenja\n");
            break;
        default:
            printf("Nepoznata operacija!\n");
            break;
        }
    }



    deleteAll(&stack);
    deleteAll(&queue);
	return 0;
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
    printf("# Delete all data ******** %d #\n", 7);
    printf("# Close the application ** %d #\n", -1);
    printf("###################################\n\n");

    printf("Enter your command:\t");
}

void stackPush(position head, int isFUll)
{

    if (isFUll == 1) {
        dropLast(head);
    }

    int value = getRandomNumber();
    position target = makeNewElement(value);

    target->next = head->next;
    head->next = target;

    printf("Pushed number %d\n", value);
}

position makeNewElement(int value)
{
    return makeNewWithPriority(value, -1);
}

position makeNewWithPriority(int value, int priority)
{
    position target = (position)malloc(sizeof(list));
    target->priority = priority;
    target->element = value;
    target->next = NULL;
    return target;
}

int getRandomNumber(void)
{
    int number = (rand() % (100 - 10 + 1)) + 10;
    return number;
}

void printList(position head)
{
    int counter = 1;

    if (head == NULL)
        printf("\n\nSTACK/QUEQUE IS EMPTY!!!\n\n");

    while (head != NULL)
    {
        if (head->priority != -1)
        {
            printf("%d) %d priority %d\n", counter, head->element, head->priority);
        }
        else {
        printf("%d) %d\n",counter, head->element);
        }

        head = head->next;
        counter++;
    }
}

void dropLast(position head)
{
    position previous = head;
    head = head->next;

    while (head->next != NULL)
    {
        previous = previous->next;
        head = head->next;
    }

    free(head);
    previous->next = NULL;
}

void stackPop(position head)
{
    if (head->next == NULL)
    {
        printf("\n\nSTACK/QUEQUE IS EMPTY!!!\n\n");
        return;
    }
    position target = head->next;

    head->next = target->next;

    printf("Poped number: %d\n", target->element);
    free(target);
}

int getRandomPriority(void)
{
    int priority = (rand() % (5 - 1 + 1)) + 1;
    return priority;
}

void queuePush(position head)
{
    int value = getRandomNumber();
    int priority = getRandomPriority();
    position target = makeNewWithPriority(value, priority);

    while (head->next != NULL && head->next->priority >= priority)
    {
        head = head->next;
    }

    target->next = head->next;
    head->next = target;
    head = target;
    printf("Pushed in queque number: %d with priority %d\n", value, priority);
}

void deleteAll(position head)
{
    position temp = head->next;

    while (head->next != NULL)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
    printf("Data is deleted!\n");
}