#include<stdio.h>
#include<Windows.h>

void shiftLeft(int* a, int* b, int* c, int* d);
void shiftRight(int* a, int* b, int* c, int* d);

int main()
{
	int x = 0;
	int y = 0;
	int z = 0;
	int w = 0;

	scanf("%d %d %d %d", &x, &y, &z, &w);

	shiftLeft(&x, &y, &z, &w);
	printf("%d %d %d %d\n", x, y, z, w);

	shiftRight(&x, &y, &z, &w);
	shiftRight(&x, &y, &z, &w);
	printf("%d %d %d %d\n", x, y, z, w);

	system("pause");
}

void shiftLeft(int* a, int* b, int* c, int* d)
{
	int temp = *a;
	*a = *b;
	*b = *c;
	*c = *d;
	*d = temp;
}

void shiftRight(int* a, int* b, int* c, int* d)
{
	int temp = *d;
	*d = *c;
	*c = *b;
	*b = *a;
	*a = temp;
}