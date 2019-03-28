#include <stdio.h>
#include <Windows.h>

long fac(int);
long my_pow(int, int);

int main(int argc, char *argv[]) {

	int i = 100;
	int *ptr = &i;
	printf("num: %d; loc: %d\n", *ptr, ptr);

	printf("x^2\t2^x\tx!\n");
	for (int i = 0; i <= 100; i++) {
		printf("%d\t%d\t%d\n", my_pow(i, 2), my_pow(2, i), fac(i));
	}
	//Werte nicht identisch, da Overflow...
	
	Sleep(10000);
	return 0;
}

long fac(int num) {
	long res = 1;
	for (int i = 1; i <= num; i++) {
		res *= i;
	}
	return res;
}

long my_pow(int a, int b) {
	long res = 1;
	for (; b > 0; b--) {
		res *= a;
	}
	return res;
}
