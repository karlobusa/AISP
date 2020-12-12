#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _skup;
typedef struct _skup skup;
typedef skup* position;

struct _skup
{
	int number;
	position next;
};

int readDataFromFile(position, char*);
int makeNewElement(position, int);
int makeIntersection(position, position, position);
int makeUnion(position, position, position);
int deleteList(position);

int main()
{
	int status = -123;
	skup prviSkup;
	skup drugiSkup;
	skup presjek;
	skup unija;

	char fileName1[102] = "skup1.txt";
	char fileName2[102] = "skup2.txt";

	prviSkup.number = 0;
	prviSkup.next = NULL;

	drugiSkup.number = 0;
	drugiSkup.next = NULL;

	unija.number = 0;
	unija.next = NULL;

	presjek.number = 0;
	presjek.next = NULL;

	printf("Prvi  skup: ");
	readDataFromFile(&prviSkup, fileName1);
	printzAll(prviSkup.next);

	printf("\n\nDrugi skup: ");
	readDataFromFile(&drugiSkup, fileName2);
	printzAll(drugiSkup.next);

	printf("\n\nUnija     : ");
	makeUnion(prviSkup.next, drugiSkup.next, &unija);
	printzAll(unija.next);

	printf("\n\nPresjek   : ");
	makeIntersection(prviSkup.next, drugiSkup.next, &presjek);
	printzAll(presjek.next);

	printf("\n\nBrisanje podataka...\n");
	deleteList(&prviSkup);
	deleteList(&drugiSkup);
	deleteList(&unija);
	deleteList(&presjek);

	status = deleteList(&prviSkup);
	if (status == 1)
		printf("Brisanje uspjesno obavljeno!\n");
	else
		printf("Brsanje neuspjesno!!!");


	printf("\ndovidenja!\n");
	getch();
	return 0;
}

int readDataFromFile(position head, char* fileName)
{
	FILE* fp = NULL;
	char buffer[1024] = "\0";
	int number = -1;

	int result = 0;



	fp = fopen(fileName, "r");


	while (!feof(fp))
	{
		fgets(buffer, 10, fp);
		if (strlen(buffer) > 0)
		{			
			result = sscanf(buffer, " %d", &number);
			result = makeNewElement(head, number);
			head = head->next;
		}
	}


	fclose(fp);
	return 0;
}

int makeNewElement(position head, int number)
{
	position temp;

	while (head->next != NULL)
	{
		head = head->next;
	}
	temp = (position)malloc(sizeof(skup));
	temp->number = number;

	temp->next = head->next;
	head->next = temp;
	return 0;
}

int printzAll(position head)
{
	while (head != NULL)
	{
		printf("%d ", head->number);
		head = head->next;
	}

	return 0;
}

int makeIntersection(position prviSkup, position drugSkup, position presjek)
{
	int status = -1;
	while (prviSkup != NULL && drugSkup != NULL)
	{
		if (prviSkup->number == drugSkup->number)
		{
			status = makeNewElement(presjek, prviSkup->number);
			prviSkup = prviSkup->next;
			drugSkup = drugSkup->next;
			presjek = presjek->next;

		}
		else if (prviSkup->number > drugSkup->number)
		{
			drugSkup = drugSkup->next;
		}
		else if (prviSkup->number < drugSkup->number)
		{
			prviSkup = prviSkup->next;
		}
	}


	return 0;
}

int makeUnion(position prviSkup, position drugiSkup, position unija)
{
	int result = -1;

	while (prviSkup != NULL && drugiSkup != NULL)
	{
		if (prviSkup->number > drugiSkup->number)
		{
			result = makeNewElement(unija, drugiSkup->number);
			drugiSkup = drugiSkup->next;
			unija = unija->next;
		}
		else if (prviSkup->number < drugiSkup->number)
		{
			result = makeNewElement(unija, prviSkup->number);
			unija = unija->next;
			prviSkup = prviSkup->next;
		}
		else {
			result = makeNewElement(unija, prviSkup->number);
			unija = unija->next;
			prviSkup = prviSkup->next;
			drugiSkup = drugiSkup->next;
		}
	}

	return 0;
}

int deleteList(position head)
{
	position temp = head->next;

	if (temp == NULL)
		return 1;

	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	return 0;
}