#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>//für int size

struct glied{
    int wert;
    struct glied *nachfolger;
};
void print_list(struct glied *);
void add_elm(struct glied *, int);
void free_all(struct glied *);
void get_int(int *);
int int_len(int);

int main(){
    struct glied *list = malloc(sizeof (struct glied));
    struct glied *letztes = NULL;
    if (list == NULL){
        perror("malloc");
    }
    int inp;
    
    get_int(&inp);
    while (inp != -1){
        if (letztes == NULL){//Testet ob es der erste Durchlauf ist
            add_elm(list, inp);
            letztes = list->nachfolger;
        }else{
            add_elm(letztes, inp);
            letztes = letztes->nachfolger;
        }
        get_int(&inp);
    }
    
    print_list(list);
    free_all(list);

    return 0;
}

//gibt Liste aus
void print_list(struct glied *ll){
    //dreht Liste um:
    struct glied *tmp = NULL;
    struct glied *prev = NULL;
    while (ll->nachfolger != NULL){
        tmp = ll->nachfolger;
        ll->nachfolger = prev;
        prev = ll;
        ll = tmp; 
    }
    ll->nachfolger = prev;
    //gibt Liste aus:
    while (ll->nachfolger != NULL){
        printf("%d\n", ll->wert);
        ll = ll->nachfolger;
    }
}

//fügt num als neues Element zu llist hinzu
void add_elm(struct glied *llist, int num){
	while (llist->nachfolger != NULL){
		llist = llist->nachfolger;
    }
	llist->nachfolger = malloc(sizeof(struct glied));
    if (llist->nachfolger == NULL){
        perror("malloc");
    }
	llist->nachfolger->wert = num;
	llist->nachfolger->nachfolger = NULL;
}

//wendet free auf alle Elemente der Liste an
void free_all(struct glied *llist){
    struct glied *tmp = llist;
    while (llist->nachfolger != NULL){
        tmp = llist->nachfolger;
        free(llist);
        llist = tmp;
    }
    free(llist);
}

//liest int ein und speichert den Wert in inp 
void get_int(int *inp){
    int len = int_len(INT_MAX)+1;
    char *strin = malloc(len);
    if (strin != NULL){
        scanf("%s", strin);
        if ((int)strlen(strin) > len){
            perror("Wrong input (to long)");
        }
        *inp = atoi(strin);
        free(strin);
    }
    else{
        perror("malloc");
    }
}

//gibt int Länge zurück
int int_len(int num){
    int i;
    for (i = 0; num >= 10; i++){
        num /= 10;
    }
    return i;
}