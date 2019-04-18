#include "ll.h"

#include "util.h"/*for: error*/
#include <stdlib.h>/*for: malloc, free*/
#include <string.h>/*for: strncpy, strcpy*/
#include <stdio.h>/*for: FILE, printf */

void print_ll(ll_node_t head)
{
	do {
		printf("%s\n",head.val);
		head = *head.next;
	}
	while(head.next);
	printf("%s\n",head.val);
}


void push(ll_node_t** head, const char* str)//works
{
	if (!*head) *head = new_node(str);
	else{
		ll_node_t *node = *head;
		while (node->next) node=node->next;
		node->next = new_node(str);
	}
}


void add(ll_node_t* head, unsigned int ind, const char * str)//works
{
	if(!head && ind) error("invalid ind for add");

	ll_node_t * prev = 0;
	ll_node_t *node = head;
	while(ind)
	{
		prev = node;
		node = node->next;
		ind--;

		if(!node && ind) error("invalid ind for add");
	}

	if(prev){
		prev->next = new_node(str);
		prev->next->next = node;
	}
	else{
		ll_node_t * temp = new_node(head->val);
		temp->next = head->next;
		strcpy(head->val,str);
		head->next = temp;
	}
}


void remove_head(ll_node_t** head)
{
	if(!head) error("removal underflow");
	
	ll_node_t * next = (*head)->next;
	free((*head)->val);
	free(*head);
	*head = next;
}

char * rem_at(ll_node_t** head, unsigned int ind)//works
{
	ll_node_t * prev = 0;
	ll_node_t *node = *head;
	while(ind)
	{
		prev = node;
		node = node->next;
		ind--;

		if(!node && ind) error("invalid ind");
	}
	char * val = node->val;
	ll_node_t * temp = node->next;
	free(node);
	if (!prev) *head = temp;
	else prev->next = temp;

	return val;
}


ll_node_t* arr_to_ll(const char** arr, int len)//works
{
	ll_node_t * head = new_node(arr[0]);
	ll_node_t * temp = head;
	for (int i = 1; i < len; ++i)
	{
		temp->next = new_node(arr[i]);
		temp = temp->next;
	}
	return head;
}



ll_node_t* new_node(const char* val)//works
{
	ll_node_t * newn = malloc(sizeof(ll_node_t));
	int len = strlen(val)+1;
	char * copy = malloc(len);
	strncpy(copy,val,len);
	newn->val = copy;
	newn->next = 0;
	return newn;
}