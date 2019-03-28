#include <stdio.h>

void append_c(char **, char);
int strinc(char *, char);

int main(int argc, char *argv[]) {
	FILE *file;
	fopen_s(&file, argv[1], "r");

	char c, letztes = '\0';
	char *cptr = (char *) malloc(1);
	*cptr = '\0';
	int zeichen = 0, words = 0, words_temp = 0, lines = 0;

	while (c = fgetc(file), c!=EOF) {

		zeichen++;
		if (c == '\n') {
			lines++;
		}
		else if (c != ' ' && (letztes == ' ' || letztes == '\n')) {
			words++;
		}
		if (strinc(cptr, c)!=0) {
			append_c(&cptr, c);
		}
		letztes = c;
	}
	words += words_temp;

	printf("Zeichen: %d\nWoerter: %d\nZeilen: %d\n(Unterschiedliche Zeichen: %d)\n", zeichen, words, lines, strlen(cptr));
	return 0;
}

void append_c(char **ptr, char c) {
	int len = strlen(*ptr);
	char *str = (char *)malloc(len + 1);
	strcpy_s(str, len + 1, *ptr);
	*ptr = (char *)malloc(len + 2);
	strcpy_s(*ptr, len + 2, str);
	(*ptr) += len;
	**ptr = c;
	(*ptr)++;
	**ptr = '\0';
	(*ptr) -= (len + 1);
}

int strinc(char *ptr, char c) {
	while (*ptr != '\0') {
		if (*ptr == c) {
			return 0;
		}
		ptr++;
	}
	return 1;
}
