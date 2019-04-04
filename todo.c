#include "todo.h"
#include <stdio.h>
#include <string.h>/*for:strcmp*/

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
ll_node_t * get_todos(FILE * fp)//works
{
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
			line[chrs+1] = 0;
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
	char flag = 0;
	int i = 0, ret;
	ll_node_t * node = args;
	while(node)
	{
		if(!(flag&1) && is_number(args->val, &ret))
		{
			flag |= 1;
			*num = ret;
			printf("got number: %d\n",ret);
		}
		else if(!(flag&2) && is_string(args->val))
		{
			flag |= 2;
			(*str) = args->val;
		}
		node = node->next;
		i++;
	}
	return flag;
}