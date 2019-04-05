#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void show_loadanim(int, int);

int main(){
	for (int i = 100; 25 < i; i -= 2){
		show_loadanim(1, i);
	}
	//show_loadanim(100, 55);
	//show_loadanim(100, 25);
	return 0;
}

void show_loadanim(int count, int speed){
	char zeichen[] = {'-', '\\', '|', '/'};
	int sleep_time = speed*1000;
	printf(" \n");
	for (; 0 < count; count--){
		printf("\033[A%c\n", zeichen[0]);
		usleep(sleep_time);
		for (int i = 1; i < 4; i++){
			printf("\033[A%c\n", zeichen[i]);
			usleep(sleep_time);
		}
	}
	printf("\033[A");
}