#include "todo.h"
#include <stdio.h>
#include <string.h>/*for:strcmp*/
#include <stdlib.h>
#include "ll.h" /*for: ll struct and methods*/
#include "util.h" /*for:MAXLINELEN*/
#include "commands.h" /*for:Command_Names, NUMCOMMANDS*/


const char* Command_Names[NUMCOMMANDS] = 
{
	"todo  \0",
	"add   \0",
	"remove\0",
	"update\0",
	"edit  \0",
	"done  \0",
	"show  \0"
};


enum
{
	TODO,
	ADD,
	REMOVE,
	UPDATE,
	EDIT,
	DONE,
	SHOW,
};



/*-- input: pathname, 
	 returns: len of dest,
	 dest = list of tods  --*/
ll_node_t *get_todos(char *file_name)//works
{
	FILE *fp = get_open_file(file_name);

	int lines, chrs;
	chrs = lines = 0;

	char line[MAXLINELEN], c = '0';

	ll_node_t * node = 0, * ret = 0;

	while(c != EOF){
		chrs = 0;
		c = fgetc(fp);

		while(c != '\n' && c != EOF && chrs < MAXLINELEN-1)
		{
			line[chrs] = c;
			chrs++;
			c = fgetc(fp);
		}

		if(chrs) 
		{
			lines++;
			line[chrs] = 0;
			push(&ret,line);//can be optimized
		}
	}
	return ret;
}



/*returns 1 if the string "g"/"G" is contained in arr, else 0*/
int get_flag(ll_node_t** head)//works
{
	if(!strcmp((*head)->val,"G") || !strcmp((*head)->val,"g"))
	{
		remove_head(head);
		return GLOBAL;
	}
	return LOCAL;
}


/*returns code for a command in args and remove_nodes the elm from args*/
int get_command(ll_node_t** head)
{
	if(!head) return TODO;

	for (int i = 0; i < NUMCOMMANDS; i++)
	{
		if(caseless_cmp(Command_Names[i],(*head)->val))
		{
			remove_head(head);
			switch(i)
			{
				case 0:
					return TODO;
				case 1:
					return ADD;
				case 2:
					return REMOVE;
				case 3:
					return UPDATE;
				case 4:
					return EDIT;
				case 5:
					return DONE;
				case 6:
					return SHOW;
				default:
					error("Match with untracked Command");
			}
		}
	}
}

/*gets the parameters for a command returns the amount of params received*/
int get_params(ll_node_t* args, char ** str, int * num)
{
	//check if a given arg contains chars or nums
	int params = 0;
	int num_param;
	char * build_str = 0, *temp = 0;

	if (is_number(args->val,&num_param))
	{
		*num = num_param;
		remove_head(&args);
	 	params |= 1;
	}
	if(args)
	{
		params |= 2;
		build_str = rem_at(&args,0);
		while(args)
		{
			build_str = concat(build_str, " ");
			temp = rem_at(&args,0);
	
			build_str = concat(build_str, temp);
			free(temp);
		}

		*str = build_str;
	}
	return params;
}