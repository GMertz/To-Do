#ifndef GUARD_COMMANDS_H
#define GUARD_COMMANDS_H
#define NUMCOMMANDS 7
#include "ll.h"

int todo(ll_node_t *, char*);
int add_todo(ll_node_t *, char*);
int rem(ll_node_t *, char*);
int update(ll_node_t *, char*);
int edit(ll_node_t *, char*);
int done(ll_node_t *, char*);
int show(ll_node_t *, char*);

#endif