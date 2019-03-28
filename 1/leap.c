#include <stdio.h>

int inp_ok(char *);

int main(int argc, char *argv[]) {
	if (argc > 1) {
		if (inp_ok(argv[1]) == 0) {
			int j = atoi(argv[1]);
			if (j % 400 == 0 || j % 4 == 0 && j % 100 != 0) {
				printf("Das Jahr %d ist ein Schaltjahr.\n", j);
			}
			else {
				printf("Das Jahr %d ist kein Schaltjahr.\n", j);
			}
		}
		else {
			printf("Fehlerhafte Eingabe.\n");
		}
	}
}

int inp_ok(char *ptr) {
	while (*ptr != '\0') {
		if (!((int)*ptr <= 57 && (int)*ptr >= 48)) {
			return 1;
		}
		ptr++;
	}
	return 0;
}
