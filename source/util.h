#ifndef UTIL
#define UTIL

#include <stdio.h>/*for: FILE*/
#include "ll.h"
#include <inttypes.h>/*uint_64_t*/
#define MAXPATHLEN 500
#define MAXLINELEN 500
#define MAXTODOS 50
#define FILENAME "todo.txt"
#define FINISHED "done.txt"

#define ABSOL(x) ((x) < 0 ? -(x) : (x))
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

char *concat(const char * source, const char * addend, const char delim);
char *substr(const char * source, int start, int end);
char *get_local_path();
char *trimmed_copy(const char * source);
int caseless_cmp(const char * a, const char * b);
int is_number(const char * str, int * num);
int is_string(const char * str);

FILE * get_open_file(const char * file_name);

char *int_to_hex(int val);
char *get_hashed_path(const char * local_path, int offset);
char *get_effective_path(char *global_path, int mode);
char *get_effective_path_local(char *path, int offset);
char *get_path_from_reg(char *path);

#endif