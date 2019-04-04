#ifndef GUARD_TODO_H
#define GUARD_TODO_H

#include "ll.h"/*for:ll_node_t */
#include <stdio.h>/*for: FILE*/

ll_node_t * get_todos(FILE * fp);
int get_flag(ll_node_t** head);
int get_command(ll_node_t** head);
int get_params(ll_node_t* args, char ** str, int * num);

#endif