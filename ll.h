#ifndef GUARD_LL_H
#define GUARD_LL_H

typedef struct ll_node_t
{
	char * val;
	struct ll_node_t * next;
}ll_node_t; 	

void print_ll(ll_node_t head);
void push(ll_node_t** head, const char* str);
void add(ll_node_t* head, unsigned int ind, const char * str);
char * remove_head(ll_node_t** head);
ll_node_t* arr_to_ll(const char** arr, int len);
ll_node_t* new_node(const char* val);

#endif