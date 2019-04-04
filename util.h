#ifndef UTIL
#define UTIL

#include <stdio.h>/*for: FILE*/
#include "ll.h"
#define MAXPATHLEN 30
#define MAXLINELEN 500
#define FILESDIR "C:\\Users\\Gmert\\code\\proj\\tod\\todfiles\\"

#define GLOBALPATH "C:\\Users\\Gmert\\code\\proj\\tod\\todfiles\\todo.txt"
#define FILEEXT ".txt"

enum
{
	LOCAL,
	GLOBAL
};


enum
{
	OK,
	FAIL
};

void error(char* str);
void safe_exit();

char* concat(char * source, char * addend);
char * get_dir_name();
char * trimmed_copy(const char * source);
int caseless_cmp(const char * a, const char * b);
int is_number(const char * str, int * num);
int is_string(const char * str);

FILE * get_open_file(char * file_name, char * mode);

/*-- input: pathname, 
	 returns: len of dest,
	 dest = list of tods  --*/
ll_node_t * get_todos(FILE * fp);

/*returns 1 if the string "g"/"G" is contained in arr, else 0*/
int get_flag(ll_node_t** head);

/*returns code for a command in arr*/
int get_command(ll_node_t** args);

/*gets the parameters for a command*/
int get_params(ll_node_t* args, char ** str, int * num);

void serialize_todos(ll_node_t todos, char* file_name);

#endif