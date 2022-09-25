#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void try(int *res) {
	int i;
	srandom(time(NULL));
	for (i = 0; i < 3; i++)
		res[i] = random()%8;
}

void printRes(int *res) {
	int i;
	for (i = 0; i < 3; i++)
		printf("%d", res[i]);
	printf("\n");
}

int gainComp(int *res) {
	//000 = 500С/5АВ = 50С /55А = 125С/7АВ = 200С/77А = 700С/
	//ААА = 250С/555 = 375С/666 = LOST/777 = WIN /
	//-TryCost = 100C
	int gain = -100;
	if (res[0] == res[1] && res[1] == res[2]) {
		gain += 250;
		if (res[0] == 0)
			gain += 250;
	}
	if (res[0] == 5) {
		gain += 50;
		if (res[1] == 5)
			gain += 75;
	} else if (res[0] == 7) {
		gain += 200;
		if (res[1] == 7)
			gain += 500;
	}
	return gain;
}

int main(int args, char *argv[]) {
	//можно ввести свои значения
	int isCustom = args > 1;
	int set[args-1];
	int setIndex = 0;
	int i;
	for (i = 0; i < args-1; i++)
		set[i] = atoi(argv[i+1]);

	int credit = 5000;
	int gain = 0;
	int res[3];
	while (1) {
		printf("You have %dC\n", credit);
		if (credit <= 0) {
			printf("You've lost: 0C\n");
			break;
		}
		if (credit > 50000) {
			printf("You've tired\n");
			break;
		}
		//перебор всех кастомных сетов и выход
		if (isCustom) {
			if (setIndex == args-1)
				break;
			int curSetNum = set[setIndex++];
			res[0] = curSetNum%1000/100;
			res[1] = curSetNum%100/10;
			res[2] = curSetNum%10;
		}
		else 
			try(res);
		printRes(res);
		
		if (res[0] == res[1] && res[1] == res[2])
			if (res[0] == 6) {
				printf("You've lost your all\n");
				break;
			} else if (res[0] == 7) {
				printf("You've won\n");
				break;
			}
		gain = gainComp(res);
		if (gain < 0)
			printf("You've lost ");
		else
			printf("You've won ");
		printf("%dC\n", gain);
		credit += gain;
		if (!isCustom)
			getchar();
	}
	return 0;
}
