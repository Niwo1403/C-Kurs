#ifndef LINKED_LIST
#define LINKED_LIST

struct LIST {
	int number;
	struct LIST *next;
};
extern int search_elm(struct LIST *llist, int num);
extern void add_elm(struct LIST *llist, int num);
extern void print_list(struct LIST *llist);
extern void init_list(struct LIST **llist, int first_elm);
extern void rmv_elm(struct LIST *llist, int num);
extern int get_elm(struct LIST *llist, int index);

#endif