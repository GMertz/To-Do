#ifndef UTIL
#define UTIL

#include <stdio.h>/*for: FILE*/
#include "ll.h"
#define MAXPATHLEN 30
#define MAXLINELEN 500
#define MAXTODOS 50
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

FILE * get_open_file(char * file_name);

/*-- input: pathname, 
	 returns: len of dest,
	 dest = list of tods  --*/

#endif