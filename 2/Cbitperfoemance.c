#include <stdio.h>

unsigned int sadd(unsigned int);
unsigned int ctz(unsigned int);
unsigned int rev(unsigned int);
unsigned int bswap(unsigned int);
unsigned int my_pow(unsigned int, unsigned int);

int main() {

	unsigned int i = 1011010100;
	printf("Nummer(1011010100): %u\n", i);
	printf("sadd(5): %u\n", sadd(i));
	printf("ctz(2): %u\n", ctz(i));
	printf("rev(10101101): %u\n", rev(i));
	printf("bswap(1101010010): %u\n", bswap(i));

	return 0;
}

unsigned int sadd(unsigned int x) {
	unsigned int ret = 0;
	while (x != 0) {
		if (x % 2 == 1) {
			ret++;
			x--;
		}
		x /= 10;
	}
	return ret;
}

unsigned int ctz(unsigned int x) {
	unsigned int ret = 0;
	while (x != 0) {
		if (x % 2 == 1) {
			break;
		}
		ret++;
		x /= 10;
	}
	return ret;
}

unsigned int rev(unsigned int x) {
	unsigned int ret = 0;
	while (x != 0) {
		ret *= 10;
		if (x % 2 != 0) {
			ret ++;
			x--;
		}
		x /= 10;
	}
	return ret;
}

unsigned int bswap(unsigned int x) {
	unsigned int ret = 0, temp = 0;
	unsigned int count = 1, i = 0;
	while (x != 0) {
		count = 1;
		temp = 0;
		for (i = 0; i < 8 && x != 0; i++) {
			if (x % 2 == 1) {
				temp += count;
				x--;
			}
			count *= 10;
			x /= 10;
		}
		ret *= my_pow(10, i);
		ret += temp;
	}
	return ret;
}

unsigned int my_pow(unsigned int a, unsigned int b) {
	unsigned int ret = 1;
	while (b != 0) {
		ret *= a;
		b--;
	}
	return ret;
}
