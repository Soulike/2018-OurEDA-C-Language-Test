#include<stdio.h>

int main()
{
	int courseNumber = 0;
	double totalCredit = 0;
	double ScoreCreditProductSum = 0;

	double currentScore = 0;
	double currentCredit = 0;

	scanf("%d", &courseNumber);

	for (int i = 0; i < courseNumber; i++)
	{
		scanf("%lf %lf", &currentScore, &currentCredit);
		totalCredit += currentCredit;
		ScoreCreditProductSum += currentScore * currentCredit;
	}

	printf("%.2lf\n", ScoreCreditProductSum / totalCredit);
}