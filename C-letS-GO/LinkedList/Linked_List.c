#include "Linked_List.h"
void print_list(struct LIST *llist){
	while (llist->next != 0){
		printf("%d ", llist->number);
		llist = llist->next;
	}
	printf("%d", llist->number);
}

void init_list(struct LIST **llist, int first_elm) {
	*llist = (struct LIST*) malloc(sizeof(struct LIST));
	(*llist)->next = 0;
	(*llist)->number = first_elm;
}

void add_elm(struct LIST *llist, int num){
	while (llist->next != 0)
		llist = llist->next;
	llist->next = (struct LIST *) malloc(sizeof(struct LIST));
	llist->next->number = num;
	llist->next->next = 0;
}

void rmv_elm(struct LIST *llist, int num){
	struct LIST *temp;
	temp = (struct LIST *) malloc(sizeof(struct LIST));
	if (llist->number == num){
		temp = llist->next;
		free(llist);
		llist = temp;
	}else{
		while (llist->next->number != num)
			llist = llist->next;

		temp = llist->next->next;
		free(llist->next);
		llist->next = temp;
	}
}

int search_elm(struct LIST *llist, int num){//beginnt bei 0
	for (int i = 0; llist != 0; i++) {
		if (llist->number == num)
			return i;
		llist = llist->next;
	}
	return (-1);
}

int get_elm(struct LIST *llist, int index) {
	while (index > 0) {
		if (llist->next != 0) {
			llist = llist->next;
		 }
		index--;
	}
	return llist->number;
}