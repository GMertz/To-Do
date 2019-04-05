#include "commands.h"
#include "ll.h"
#include "util.h"/*for: get_open_file */
#include "todo.h"
#include <stdio.h>

//prints todos
int todo(ll_node_t * head, char * file_name)//works
{
	int i = 0;
	ll_node_t * todos = 0;

	if(todos = get_todos(file_name))
	{
		while(todos)
		{
			printf("%d) %s\n",i,todos->val);
			todos = todos->next;
			i++;
		}
	}
	else{
		error("No todos to print");
	}

	return OK;
}

//add a todo
int add_todo(ll_node_t * head, char * file_name)
{
	int ind; 
	char *message = 0;
	
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

	serialize_todos(*todos, file_name);
	return OK;
}

//remove a todo
int rem(ll_node_t * head, char * file_name)
{
	int ind; 
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
	
	serialize_todos(*todos, file_name);
	return OK;
}

//update a todo
int update(ll_node_t * head, char * file_name)
{
	// printf("doing update!\n");
	// return OK;

	ll_node_t * todos = get_todos(file_name);
}

//open the todo file for opening
int edit(ll_node_t * head, char * file_name)
{
	// printf("doing edit!\n");
	// return OK;

	ll_node_t * todos = get_todos(file_name);
}


//finish a todo
int done(ll_node_t * head, char * file_name)
{
	// printf("doing done!\n");
	// return OK;

	ll_node_t * todos = get_todos(file_name);
}

//show finished todos
int show(ll_node_t * head, char * file_name)
{
	// printf("doing show!\n");
	// return OK;

	ll_node_t * todos = get_todos(file_name);
}
