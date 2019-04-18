#include "ll.h"/*for:ll_node_t, arr_to_ll */
#include "todo.h"/*for:get_flag, get_command */
#include "util.h" /*for: concat, get_dir_name, FILEEXT */
#include "commands.h"/*for: todo, add_todo, rem, update, edit, done, show */


void (*const COMM[NUMCOMMANDS])(ll_node_t * head, const char *path_name) = 
{
	todo,
	add_todo,
	rem,
	update,
	edit,
	done,
	show,
	help,
	swap
};

int main(int argv, const char **argc)
{
	#ifndef GLOBALPATH
		error("No Global path specified!");
		return 1;
		
	#else

		int scope, command;
		char *path_name = 0;
		ll_node_t* args = 0;

	if (argv == 1)
	{ 
		scope = LOCAL;
		command = 0;
	}
	else
	{
		args = arr_to_ll(&argc[1], argv-1);
		scope = get_flag(&args);
		command = get_command(&args);
	}

		char *effective_path = get_effective_path(GLOBALPATH, scope);
		COMM[command](args, effective_path);

	#endif
}