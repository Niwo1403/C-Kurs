#include <stdio.h>
#include <Windows.h>

int matoi(char *);
int ilen(int);
void mitoa(char **, int);

int main(int argc, char *argv[]) {

	printf("123 zu %d\n456 zu ", matoi("123"));

	char *ptr;
	mitoa(&ptr, 456);
	fputs(ptr, stdout);

	Sleep(5000);
	return 0;
}

int matoi(char *ptr) {
	int ret = 0;
	while (*ptr != '\0') {
		ret *= 10;
		ret += (*ptr) - '0';
		ptr++;
	}
	return ret;
}

int ilen(int num) {
	int ret = 1;
	while (num > 9) {
		ret++;
		num /= 10;
	}
	return ret;
}

void mitoa(char **ptr, int num) {
	int len = ilen(num);
	*ptr = (char *)malloc(len + 1);
	(*ptr) += len;
	(**ptr) = '\0';
	for (int i = 0; i < len; i++) {
		(*ptr)--;
		**ptr = (char)((num % 10) + '0');
		num /= 10;
	}
}
