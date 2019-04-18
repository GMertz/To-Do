#ifndef GUARD_TODO_H
#define GUARD_TODO_H

#include "ll.h"/*for:ll_node_t */
#include <stdio.h>/*for: FILE*/

enum PARAM
{
	P_NONE,
	P_NUM,
	P_STR,
	P_BOTH
};

ll_node_t *get_todos(const char *file_name);
int get_flag(ll_node_t **head);
int get_command(ll_node_t **head);
int get_params(ll_node_t *args, char **str, int *num);
void serialize_todos(ll_node_t *todos, const char *file_name);

#endif