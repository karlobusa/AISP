#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _polynomial;
typedef _polynomial polynomial;
typedef polynomial* position;
struct _polynomial {
	int koeficijent;
	int exponent;

	position next;
};

int readDataFromFile(position, char*);
int addKoeficientToPolynamial(position, int, int);
int createNewElementAndInsert(position, int, int);
int printzAll(position);
int insert(position, position);
int calculatePolynomialSum(position, position, position);
position createNewElement(int, int);
int calculatePolynomialProduct(position, position, position);
int printDataToFIle(position, char*);
int deleteList(position);


int main(int argc, char** argv)
{
	int result = -6;
	char fileName1[124] = "poly1.txt";
	char fileName2[124] = "poly2.txt";
	char sumResultFile[124] = "sumResult.txt";
	char productResultFIle[124] = "productResult.txt";

	polynomial poly1;
	polynomial poly2;
	polynomial sum;
	polynomial product;


	poly1.koeficijent = 0;
	poly1.exponent = 0;
	poly1.next = NULL;

	poly2.koeficijent = 0;
	poly2.exponent = 0;
	poly2.next = NULL;

	sum.koeficijent = 0;
	sum.exponent = 0;
	sum.next = NULL;

	product.koeficijent = 0;
	product.exponent = 0;
	product.next = NULL;

	printf("Reading first polynomial data from file...\n");
	result = readDataFromFile(&poly1, fileName1);
	result = printzAll(poly1.next);

	printf("Reading second polynomial data from file...\n");
	result = readDataFromFile(&poly2, fileName2);
	result = printzAll(poly2.next);

	printf("Sum of polynomials...\n");
	result = calculatePolynomialSum(poly1.next, poly2.next, &sum);
	result = printzAll(sum.next);

	printf("Product of polynomials...\n");
	result = calculatePolynomialProduct(poly1.next, poly2.next, &product);
	result = printzAll(product.next);

	result = printDataToFIle(sum.next, sumResultFile);
	result = printDataToFIle(sum.next, productResultFIle);

	result = -1;

	result = deleteList(&poly1);
	result = deleteList(&poly2);
	result = deleteList(&sum);
	result = deleteList(&product);



	return 0;
}

int readDataFromFile(position head, char* fileName)
{
	FILE* fp = NULL;
	char buffer[1024] = "\0";
	int status = 0;
	int koeficijent = -1;
	int exponent = -1;

	fp = fopen(fileName, "r");

	while (!feof(fp))
	{
		fgets(buffer, 1023, fp);
		if (strlen(buffer) > 0)
		{
			sscanf(buffer, " %d %d", &koeficijent, &exponent);
			status = addKoeficientToPolynamial(head, koeficijent, exponent);
		}
	}


	fclose(fp);
	return 0;
}

int printDataToFIle(position head, char* fileName)
{
	FILE* fp = NULL;
	char buffer[1024] = "\0";
	int koeficient = -1;
	int exponent = -1;

	fp = fopen(fileName, "w");

	while (head != NULL)
	{
		koeficient = head->koeficijent;
		exponent = head->exponent;
		fprintf(fp, "%d %d\n", koeficient, exponent);
		head = head->next;
	}
	return 0;
}

int addKoeficientToPolynamial(position head, int koeficient, int exponent)
{
	position previous = head;

	while (previous->next != NULL && previous->next->exponent > exponent)
	{
		previous = previous->next;
	}

	if (previous->next == NULL || previous->next->exponent < exponent)
	{
		return createNewElementAndInsert(previous, koeficient, exponent);
	}

	previous->next->koeficijent = previous->next->koeficijent + koeficient;
	return 0;
}

int createNewElementAndInsert(position previous, int koeficient, int exponent)
{
	position target = createNewElement(koeficient, exponent);
	return insert(previous, target);
}

position createNewElement(int koeficient, int exponent)
{
	position target = NULL;
	target = (position)malloc(sizeof(polynomial));
	if (target == NULL)
		return NULL;
	target->koeficijent = koeficient;
	target->exponent = exponent;
	target->next = NULL;

	return target;

}

int insert(position previous, position target)
{
	target->next = previous->next;
	previous->next = target;

	return 0;
}

int printzAll(position head) {

	while (head != NULL)
	{
		printf("%d %d\n", head->koeficijent, head->exponent);
		head = head->next;
	}

	return 0;
}

int calculatePolynomialSum(position poly1, position poly2, position sum) {
	int result = 0;

	while (poly1 != NULL && poly2 != NULL)
	{
		if (poly1->exponent > poly2->exponent)
		{
			result = createNewElementAndInsert(sum, poly1->koeficijent, poly1->exponent);
			poly1 = poly1->next;
		}
		else if (poly1->exponent < poly2->exponent)
		{
			result = createNewElementAndInsert(sum, poly2->koeficijent, poly2->exponent);
			poly2 = poly2->next;
		}
		else {
			result = createNewElementAndInsert(sum, poly1->koeficijent + poly2->koeficijent, poly1->exponent );
			poly1 = poly1->next;
			poly2 = poly2->next;
		}

		sum = sum->next;
	}

	while (poly1 != NULL)
	{
		result = createNewElementAndInsert(sum, poly1->koeficijent, poly1->exponent);
		poly1 = poly1->next;
		sum = sum->next;
	}

	while (poly2 != NULL)
	{
		result = createNewElementAndInsert(sum, poly2->koeficijent, poly2->exponent);
		poly2 = poly2->next;
		sum = sum->next;
	}
	return 0;
}

int calculatePolynomialProduct(position poly1, position poly2, position product)
{
	int result = 0;
	position bookmark = poly2;

	while (poly1 != NULL)
	{
		poly2 = bookmark;

		while (poly2 != NULL)
		{
			result = addKoeficientToPolynamial(product, poly1->koeficijent * poly2->koeficijent, poly1->exponent + poly2->exponent);
			poly2 = poly2->next;
		}
		poly1 = poly1->next;
	}
	return 0;
}

int deleteList(position head)
{
	position temp = head->next;


	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);	
	}

	return 0;
}