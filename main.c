#include <stdio.h>
#include <stdlib.h>

double f(double x);
double g(double x);

int main(int args, char *argv[]) {
	if (args > 2) {
		printf("Too much arguments\n");
		return 1;
	}
	double x = 0.0;
	if (args != 1)  {
		char *endptr;
		x = strtod(argv[1], &endptr);
	}
	printf("// f(x)=exp(−∣x∣)sin(x) //\n");
	printf("// g(x)=exp(−∣x∣)cos(x) //\n");
	printf("\tx = %lf\n", x);
	printf("\tf(x)=%lf\n", f(x));
	printf("\tg(x)=%lf\n", g(x));
	return 0;
}
