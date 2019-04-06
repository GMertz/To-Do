#ifndef UTIL
#define UTIL

#include <stdio.h>/*for: FILE*/
#include "ll.h"
#define MAXPATHLEN 500
#define MAXLINELEN 500
#define MAXTODOS 50
#define FILENAME ".todo.txt"
#define FINISHED ".done.txt"


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

char* concat(const char * source, const char * addend);
char* substr(const char * source, int start, int end);
char * get_local_path();
char * trimmed_copy(const char * source);
int caseless_cmp(const char * a, const char * b);
int is_number(const char * str, int * num);
int is_string(const char * str);

FILE * get_open_file(char * file_name);

#endif