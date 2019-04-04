#include "ll.h"/*for:ll_node_t, arr_to_ll */
#include "todo.h"/*for:get_flag, get_command */
#include "util.h" /*for: concat, get_dir_name, FILEEXT */
#include "commands.h"/*for: todo, add_todo, rem, update, edit, done, show */


int (*const COMM[NUMCOMMANDS])(ll_node_t*, char*) = 
{
	todo,
	add_todo,
	rem,
	update,
	edit,
	done,
	show
};

//tod
//tod {g} add # do this thing 
//tod remove #
//tod update # new todo
//tod edit 
//tod done #
//tod show


int main(int argv, const char **argc)
{
	if(argv == 1) COMM[0](0,GLOBALPATH);
	else
	{
		ll_node_t* args = arr_to_ll(&argc[1], argv-1);
		char* file_name;

		if(get_flag(&args) == GLOBAL) file_name = GLOBALPATH;
		else file_name = GLOBALPATH;//file_name = concat(FILESDIR, concat(get_dir_name(),FILEEXT));
		//need to encode paths

		int command_code = get_command(&args);
		printf("%d\n", command_code);
		COMM[command_code](args,file_name);
	}
}