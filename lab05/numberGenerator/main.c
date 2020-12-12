#include <stdio.h>

int main(int argc, char** arhv)
{
	FILE* fp = NULL;
	int brojac = 0;
	int i = 0;

	printf("Do kojeg broja generiram visekratnike broja 2?\n");
	scanf(" %d", &brojac);


	fp = fopen("skup1.txt", "w");

	while (i <= brojac)
	{
		i += 2;
		fprintf(fp, " %d\n", i);
	}
	fclose(fp);

	printf("Do kojeg broja generiram visekratnike broja 3?\n");
	scanf(" %d", &brojac);

	i = 0;
	fp = fopen("skup2.txt", "w");

	while (i <= brojac)
	{
		i += 3;
		fprintf(fp, " %d\n", i);
	}
	fclose(fp);

	getch();

	return 0;
}