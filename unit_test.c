#include "ll.h"/*for:ll_node_t, arr_to_ll */
#include "todo.h"/*for:get_flag, get_command */
#include "util.h" /*for: concat, get_dir_name, FILEEXT */
#include "commands.h"/*for: todo, add_todo, rem, update, edit, done, show */

int main(int argv, const char **argc)
{

	ll_node_t * args = arr_to_ll(&argc[1], argv-1);
	int num;
	char * str;
	switch(get_params(args,&str,&num))
	{
		case 1:
			printf("%s %d\n",str,num);
			break;
		case 2:
			printf("%s %d\n",str,num);
			break;
		default:
			printf("no params\n");
		//serialize_todos(*args,concat(FILESDIR,"thisisatest.txt"));
	}
}