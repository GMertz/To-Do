#include "commands.h"
#include "ll.h"
#include "util.h"/*for:get_open_file */
#include <stdio.h>

//prints todos
int todo(ll_node_t * head, char * file_name)//works
{
	// printf("doing TODO!\n");
	// return OK;

	FILE *fp = get_open_file(file_name,"r");
	int i = 0;
	ll_node_t * todos;
	if(fp && (todos = get_todos(fp)))
	{
		while(todos)
		{
			printf("%d) %s\n",i,todos->val);
			todos = todos->next;
			i++;
		}
	}
	else{
		fclose(fp);
		error("No todos to print");
	}

	fclose(fp);
	return OK;
}

//add a todo
int add_todo(ll_node_t * head, char * file_name)
{
	// printf("doing ADD_TODO!\n");
	// return OK;

	FILE *fp = get_open_file(file_name,"r+");

	int ind; char* message;
	switch(get_params(head, &message,&ind))
	{
		case 1:
			get_todos(fp);
			break;
		case 2:
			get_todos(fp);
			break;
		default:
			fclose(fp);
			error("nothing to add!");
	}

	fclose(fp);
	return OK;
}

//remove a todo
int rem(ll_node_t * head, char * file_name)
{
	// printf("doing REM!\n");
	// return OK;

	FILE *fp = get_open_file(file_name,"r+");
}

//update a todo
int update(ll_node_t * head, char * file_name)
{
	// printf("doing update!\n");
	// return OK;

	FILE *fp = get_open_file(file_name,"r+");
}

//open the todo file for opening
int edit(ll_node_t * head, char * file_name)
{
	// printf("doing edit!\n");
	// return OK;

	FILE *fp = get_open_file(file_name,"r+");
}


//finish a todo
int done(ll_node_t * head, char * file_name)
{
	// printf("doing done!\n");
	// return OK;

	FILE *fp = get_open_file(file_name,"r+");
}

//show finished todos
int show(ll_node_t * head, char * file_name)
{
	// printf("doing show!\n");
	// return OK;

	FILE *fp = get_open_file(file_name,"r+");
}
