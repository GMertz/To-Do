#include "ll.h"/*for:ll_node_t, arr_to_ll */
#include "todo.h"/*for:get_flag, get_command */
#include "util.h" /*for: concat, get_dir_name, FILEEXT */
#include "commands.h"/*for: todo, add_todo, rem, update, edit, done, show */


void (*const COMM[NUMCOMMANDS])(ll_node_t*, const char*) = 
{
	todo,
	add_todo,
	rem,
	update,
	edit,
	done,
	show
};

int main(int argv, const char **argc)
{
	if(argv == 1) COMM[0](0,get_local_path());
	else
	{
		ll_node_t* args = arr_to_ll(&argc[1], argv-1);
		char* path_name;

		if (get_flag(&args) == GLOBAL) path_name = GLOBALPATH;
		else path_name = get_local_path();

		int command_code = get_command(&args);
		COMM[command_code](args,path_name);
	}
}