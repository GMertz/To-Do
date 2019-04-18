#ifndef GUARD_COMMANDS_H
#define GUARD_COMMANDS_H
#define NUMCOMMANDS 9
#include "ll.h"/*for: ll_node_t type*/

void todo(ll_node_t *, const char* path_name);
void add_todo(ll_node_t *, const char* path_name);
void rem(ll_node_t *, const char* path_name);
void update(ll_node_t *, const char* path_name);
void edit(ll_node_t *, const char* path_name);
void done(ll_node_t *, const char* path_name);
void show(ll_node_t *, const char* path_name);
void swap(ll_node_t *, const char* path_name);
void help(ll_node_t *, const char* path_name);

#endif