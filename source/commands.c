#include "commands.h"

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
	int line_num = 0;
	ll_node_t * todos = 0;

	char *file_name = concat(path_name,FILENAME);

	if(todos = get_todos(file_name))
	{
		while(todos)
		{
			printf("%d) %s\n",line_num, todos->val);
			todos = todos->next;
			line_num++;
		}
	}
	else{
		error("No todos to print");
	}

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

	char *file_name = concat(path_name,FILENAME);

	ll_node_t * todos = get_todos(file_name);

	switch(get_params(head, &message, &ind))
	{
		case 2:
			push(&todos, message);
			break;
		case 3:
			add(todos,ind, message);
			break;
		default:
			error("nothing to add!");
	}

	printf("%s added!",message);

	serialize_todos(todos, file_name);
}


/*
	input: a linked list of args and path_name
		reads file at path_name+.todo.txt and gathers each line into a linkedlist
	then removes an entry at index then writes the linkedlist to path_name+.todo.txt
*/
void rem(ll_node_t * head, const char *path_name)
{
	int ind; 
	char *file_name = concat(path_name,FILENAME);

	ll_node_t * todos = get_todos(file_name);

	switch(get_params(head, 0, &ind))
	{
		case 1:
			printf("%s removed!",rem_at(&todos, ind));
			break;
		case 3:
			printf("%s removed!",rem_at(&todos, ind));
			break;
		default:
			error("nothing to remove!");
	}
	
	serialize_todos(todos, file_name);
}


/*
	input: a linked list of args and path_name
		equivalent to rem(ind) followed by add_todo(ind)
	
*/
void update(ll_node_t * head, const char *path_name)
{
	int ind; 
	char *message = 0;

	char *file_name = concat(path_name,FILENAME);

	ll_node_t * todos = get_todos(file_name);

	switch(get_params(head, &message, &ind))
	{
		case 3:
			add(todos,ind+1, message);
			rem_at(&todos,ind);
			break;
		default:
			error("nothing to update!");
	}

	printf("%s updated!",message);

	serialize_todos(todos, file_name);
}

/*
	opens the file at path_name for editing 
*/
void edit(ll_node_t * head, const char *path_name)
{
	char *file_name = concat(path_name,FILENAME);
	system(file_name);
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

	char *file_name = concat(path_name,FILENAME);
	ll_node_t * todos = get_todos(file_name);

	int num_params = get_params(head, 0, &ind);
	if(num_params == 1 || num_params == 3)
	{
		char *finished = rem_at(&todos, ind);
		FILE *fp = fopen(concat(path_name,FINISHED),"a");

		fputs(finished,fp);
		fputc('\n',fp);
		printf("finished: %s!",finished);
	}
	else
	{
		error("nothing to remove!");
	}
	
	serialize_todos(todos, file_name);
}

/*
	input: a linked list of args and path_name
		reads file at path_name+.done.txt and gathers each line into a linkedlist
		then prints the list, numbered
*/
void show(ll_node_t * head, const char *path_name)
{
	ll_node_t *todos =  get_todos(concat(path_name,FINISHED));
	int i = 0;
	while(todos)
	{
		printf("%d) %s\n",i, todos->val);
		todos = todos->next;
		i++;
	}
}
