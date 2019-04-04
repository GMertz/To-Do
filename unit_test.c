#include "ll.h"/*for:ll_node_t, arr_to_ll */
#include "todo.h"/*for:get_flag, get_command */
#include "util.h" /*for: concat, get_dir_name, FILEEXT */
#include "commands.h"/*for: todo, add_todo, rem, update, edit, done, show */

int main(int argv, const char **argc)
{
	if(argv > 1)
	{
		ll_node_t * args = arr_to_ll(&argc[1], argv-1);
		push(&args, "woops");
		push(&args, "woops1");
		push(&args, "woops2");
		push(&args, "woops3");
		push(&args, "woops4");
		push(&args, "woops5");
		serialize_todos(*args,concat(GLOBALPATH,"thisisatest.txt"));
	}


}