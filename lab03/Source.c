#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENTH 120

typedef struct osoba* pointer;
struct osoba {
	char name[NAME_LENTH];
	char surname[NAME_LENTH];
	int yearOfBirth;
	pointer next;
};

int insertOnBeginning(pointer);
int printzAll(pointer);
int insertOnEnd(pointer);
int findElement(pointer);
pointer findPrevAdress(pointer, int);
int deleteElement(pointer, char);
pointer makeNewPerson(char*, char*, int);
int getDataFromUser(char*, char*, int*);
int insertBeforeSurname(pointer);
int insertAfterSurname(pointer);
int sortListBySurname(pointer);
int printDataTOFile(pointer);
int readDataFromFile(pointer);


int main(int argc, char** argv)
{

	struct osoba head;
	head.next = NULL;

	int status = 0;
	int target = 0;
	int izbornik = 0;


	do
	{

		printf("\n\n ######### Izbornik: ###########3\n");
		printf("1\t dodaj osobu na pocetak liste:\n");
		printf("2\t dodaj osobu na kraj liste:\n");
		printf("3\t ispisi listu:\n");
		printf("4\t dodaj osobu NAKON prezimena:\n");
		printf("5\t ddaj osobu PRIJE prezimena:\n");
		printf("6\t pronadi osobu po prezimenu:\n");
		printf("7\t izbrisi element po prezimenu:\n");
		printf("8\t sortiraj listu po prezimenu:\n");
		printf("9\t Upisi listu u datoteku\n");
		printf("10\t Procitaj listu iz datoteke\n");
		printf("-1\t IZLAZ\n");

		scanf(" %d", &izbornik);


		switch (izbornik)
		{
		case 1:
			printf("Unosis osobu na pocetak liste!\n");
			status = insertOnBeginning(&head);
			break;
		case 2:
			printf(" Unosis osobu na kraj liste\n");
			status = insertOnEnd(&head);
			break;
		case 3:
			status = printzAll(head.next);
			break;
		case 4:
			status = insertAfterSurname(&head);
			break;
		case 5:
			status = insertBeforeSurname(&head);
			break;
		case 6:
			status = findElement(&head);
			break;
		case 7:
			break;
		case 8:
			status = sortListBySurname(&head);
			break;
		case 9:
			status = printDataTOFile(head.next);
			break;
		case 10:
			status = readDataFromFile(&head);
		case -1:
			break;
		default:
			printf("\Nepoznata operacija!!!\n");
			break;
		}



	} while (izbornik != -1);



	return 0;
}

int insertOnBeginning(pointer head) {

	int status = 0;
	char name[125] = "\0";
	char surname[125] = "\0";
	int yearOfBirth = -1;
	pointer temp = NULL;

	status = getDataFromUser(name, surname, &yearOfBirth);

	temp = makeNewPerson(name, surname, yearOfBirth);


	temp->next = head->next;
	head->next = temp;

	return 0;
}

int insertOnEnd(pointer head) {
	int status = 0;
	char name[125] = "\0";
	char surname[125] = "\0";
	int yearOfBirth = -1;
	pointer temp = NULL;


	while (head->next != NULL)
	{
		head = head->next;
	}
	status = getDataFromUser(name, surname, &yearOfBirth);
	temp = makeNewPerson(name, surname, yearOfBirth);

	head->next = temp;
	return 0;
}
int insertBeforeSurname(pointer head)
{
	int status = 0;
	char name[125] = "\0";
	char surname[125] = "\0";
	char target[125] = "\n";
	int yearOfBirth = -1;
	pointer temp = NULL;

	printf("Unesi prije kojeg prezimena zelis unit novu osobu: ");
	scanf(" %s", target);

	while (strcmp(target, head->next->surname) != 0)
	{
		head = head->next;
	}

	status = getDataFromUser(name, surname, &yearOfBirth);

	temp = makeNewPerson(name, surname, yearOfBirth);

	temp->next = head->next;
	head->next = temp;


	return 0;
}

int insertAfterSurname(pointer head)
{
	int status = 0;
	char name[125] = "\0";
	char surname[125] = "\0";
	char target[125] = "\n";
	int yearOfBirth = -1;
	pointer temp = NULL;

	printf("Unesi poslije kojeg prezimena zelis unit novu osobu: ");
	scanf(" %s", target);

	while (strcmp(target, head->surname) != 0)
	{
		head = head->next;
	}

	status = getDataFromUser(name, surname, &yearOfBirth);

	temp = makeNewPerson(name, surname, yearOfBirth);

	temp->next = head->next;
	head->next = temp;


	return 0;
}



int printzAll(pointer head) {

	while (head != NULL)
	{
		printf("Ime: %s\t Prezime: %s \t Godiste: %d \n", head->name, head->surname, head->yearOfBirth, head);
		head = head->next;
	}
	return 0;
}

int findElement(pointer head) {

	int result = 0;
	char target[124] = "\0";

	printf("Koje prezime zelis pronaci?");
	scanf(" %s", target);

	while (strcmp(target, head->surname) != 0)
	{
		head = head->next;
		result++;
	}


	if (head->next == NULL)
	{
		printf("Nije pronaden\n");
		return -1;
	}

	printf("Osoba %s %s rodjena %d se nalazi na poziciji %d", head->name, head->surname, head->yearOfBirth, result);

	return result;
}

pointer findPrevAdress(pointer head, int target)
{
	pointer temp = head;
	head = head->next;

	while (head->yearOfBirth != target && head->next != NULL)
	{
		temp = head;
		head = head->next;
	}

	return temp;
}

int deleteElement(pointer head, char target) {

	pointer temp;
	head = findPrevAdress(head, target);

	temp = head->next;
	head->next = temp->next;

	free(temp);
	return 0;
}

pointer makeNewPerson(char* name, char* surname, int yearOfBirth)
{
	pointer temp = NULL;

	temp = (pointer)malloc(sizeof(struct osoba));

	strcpy(temp->name, name);
	strcpy(temp->surname, surname);
	temp->yearOfBirth = yearOfBirth;
	temp->next = NULL;

	return temp;
}

int getDataFromUser(char* name, char* surname, int* yearOfBirth)
{
	printf("Unesi sljedece podatke:\n");
	printf("Ime:");
	scanf(" %s", name);

	printf("Prezime:");
	scanf(" %s", surname);

	printf("godinu rodjenja:");
	scanf(" %d", yearOfBirth);

	return 0;
}

int sortListBySurname(pointer head) //bubble sort
{
	pointer prevPositon, position, end, temp;

	end = NULL;

	while (head->next != end)
	{
		prevPositon = head;
		position = head->next;
		while (position->next != end)
		{
			if (strcmp(position->surname, position->next->surname) > 0)
			{
				temp = position->next;
				position->next = temp->next;
				prevPositon->next = temp;
				temp->next = position;

				position = temp;

			}
			prevPositon = position;
			position = position->next;
		}
		end = position;
	}

	return 0;
}

int printDataTOFile(pointer head)
{

	FILE* fp = NULL;

	fp = fopen("data.txt", "w");

	while (head != NULL)
	{
		fprintf(fp, "%s %s %d\n", head->name, head->surname, head->yearOfBirth);
		head = head->next;
	}


	fclose(fp);
	return 0;
}

int readDataFromFile(pointer head)
{
	FILE* filePtr = NULL;
	char buffer[1021] = "\0";
	char name[124] = "\0";
	char surname[124] = "\0";
	int yearOfBirth = 0;
	pointer temp = NULL;

	filePtr = fopen("data.txt", "r");

	while (!(feof(filePtr)))
	{
		strcpy(buffer, "\0");
		strcpy(name, "\0");
		strcpy(surname, "\0");
		yearOfBirth = 0;

		fgets(buffer, 1020, filePtr);
		if (strlen(buffer) > 1)
		{


			while (head->next != NULL)
			{
				head = head->next;
			}
			sscanf(buffer, " %s %s %d", name, surname, &yearOfBirth);
			printf(" %s\n", name);

			temp = makeNewPerson(name, surname, yearOfBirth);
			head->next = temp;
			temp->next = NULL;

		}


	}
	fclose(filePtr);
	return  0;
}