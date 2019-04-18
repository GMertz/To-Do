#include "commands.h"
#include <string.h> /*strncpy, strlen*/
#include "ll.h"/*for: ll_node_t type and methods*/
#include "util.h"/*for: concat, error*/
#include "todo.h"/*for: get_todos, get_params, serialize todos*/
#include <stdio.h>/*for: printf, */
#include <stdlib.h>/*for: system, */

/*
	input: a linked list of args and path_name
		reads file at path_name+.todo.txt and prints each line, numbered
*/

void todo(ll_node_t * head, const char *path_name)//works
{
	int line_num = 1;
	ll_node_t * todos = 0;

	if ((todos = get_todos(path_name))->next)
	{
		todos=todos->next;
		while (todos)
		{
			printf("%d) %s\n",line_num, todos->val);
			todos = todos->next;
			line_num++;
		}
	}
	else error("Nothing here");
}

/*
	input: a linked list of args and path_name
		reads file at path_name+.todo.txt and gathers each line into a linkedlist
	then adds an entry at an index (entry and index are pulled from head)
	if no index is specified, new entry is added to the end, then writes the linkedlist
	to path_name+.todo.txt
*/
void add_todo(ll_node_t * head, const char *path_name)
{
	int ind; 
	char *message = 0;

	ll_node_t * todos = get_todos(path_name);

	switch(get_params(head, &message, &ind))
	{
		case P_STR:
			push(&todos, message);
			break;
		case P_BOTH:
			add(todos, ind, message);
			break;
		default:
			error("nothing to add!");
	}

	printf("%s added!",message);
	serialize_todos(todos, path_name);
}


/*
	input: a linked list of args and path_name
		reads file at path_name+.todo.txt and gathers each line into a linkedlist
	then removes an entry at index then writes the linkedlist to path_name+.todo.txt
*/
void rem(ll_node_t * head, const char *path_name)
{
	int ind, params = 0; 

	ll_node_t * todos = get_todos(path_name);
	if ((params = get_params(head, 0, &ind)) && ind > 0 && (params == P_NUM || params == P_BOTH)){

		printf("%s removed!",rem_at(&todos, ind));
		serialize_todos(todos, path_name);
	}
	else error("nothing to remove!");
}


/*
	input: a linked list of args and path_name
		equivalent to rem(ind) followed by add_todo(ind)
	
*/
void update(ll_node_t * head, const char *path_name)
{
	int ind; 
	char *message = 0;

	ll_node_t * todos = get_todos(path_name);

	if (get_params(head, &message, &ind) == P_BOTH && ind != 0)
	{
		add(todos,ind+1, message);
		rem_at(&todos,ind);
		
		printf("%s updated!",message);
		serialize_todos(todos, path_name);
			
	}
	else error("nothing to update!");
}

/*
	opens the file at path_name for editing 
*/
void edit(ll_node_t * head, const char *path_name)
{
	system(path_name);
}


/*
	input: a linked list of args and path_name
		reads file at path_name+.todo.txt and gathers each line into a linkedlist,
	removes an entry at an index (index is pulled from head). the removed todo is
	appended to path_name+.done.txt and the new list of todos is written to path_name+.todo.txt
*/
void done(ll_node_t * head, const char *path_name)
{
	int ind;
	ll_node_t * todos = get_todos(path_name);

	int num_params = get_params(head, 0, &ind);
	if (num_params == P_NUM || num_params == P_BOTH && ind != 0)
	{
		char *finished = rem_at(&todos, ind);
		
		char temp[MAXPATHLEN];
		strncpy(temp, path_name, MAXPATHLEN);
		temp[strlen(temp)-4] = 0;
		char *done_path = concat(temp,FINISHED,0);

		FILE *fp = fopen(done_path,"a");
		fputs(finished,fp);
		fputc('\n',fp);
		printf("finished: %s!",finished);

		free(done_path);
		serialize_todos(todos, path_name);
	}
	else error("nothing to remove!");
	
	
}

/*
	input: a linked list of args and path_name
		reads file at path_name+done.txt and gathers each line into a linkedlist
		then prints the list, numbered
*/
void show(ll_node_t * head, const char *path_name)
{
	char temp[MAXPATHLEN];
	strncpy(temp, path_name, MAXPATHLEN);
	temp[strlen(temp)-4] = 0;
	char *done_path = concat(temp,FINISHED,0);

	ll_node_t *todos =  get_todos(done_path);
	int i = 1;
	while (todos)
	{
		printf("%d) %s\n",i, todos->val);
		todos = todos->next;
		i++;
	}
	free(done_path);
}


/*
	print a list of command descriptions
*/
void help(ll_node_t *head, const char* path_name)
{
	error("unimplemented cmd");
}

/*
	swap the order of two todos
*/
void swap(ll_node_t *head, const char* path_name)
{
	error("unimplemented cmd");
}
