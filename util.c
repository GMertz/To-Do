#include "util.h"
#include <stdio.h>/*for: printf, FILE, fopen*/
#include <string.h>/*for: strncpy, strlen*/
#include <stdlib.h>/*for: malloc*/
#include <unistd.h>/*for: getcwd*/


void error(char* str)
{
	printf("Error: %s\n",str);
	safe_exit();
}

void safe_exit()
{
	exit(0);
}

char *concat(const char * source, const char * addend)//works
{
	int len_s, len_a;
	len_s = len_a = 0;

	len_s = strlen(source);
	len_a = strlen(addend);

	char * ret = malloc(len_s + len_a+1);

	strncpy(ret,source,len_s);//copy source to ret
	strncpy(&ret[len_s],addend,len_a+1);//copy addend

	return ret;
}

char *substr(const char * source, int start, int end)
{
	int len = strlen(source), size = end-start;

	if(size > len || start < 0 || end > len-1 || size < 0)
		return 0;

	char *substr = malloc(size+1);

	for (int i = 0; i < size; ++i)
	{
		substr[i] = source[start+i];
	}

	substr[size] = 0;
	return substr;
}

char * get_local_path()//works
{
	char buf[MAXPATHLEN];

	getcwd(buf,MAXPATHLEN);
	return concat(buf,"\\");
}

//given a string, returns the minimum size string to hold source
char * trimmed_copy(const char * source)//maybe works
{
	int i = strlen(source);
	char *ret = malloc(i+1);
	strncpy(ret,source,i);
	ret[i] = 0;
	return ret;
}

int caseless_cmp(const char * a, const char * b)//works
{
	if (!a || !b) return 0;
	
	while (*a && *b)
	{
		int dif = *a - *b;
		if (dif != 32 && dif != 0 && dif != -32) return 0;
		a++;
		b++;
	}
	return 1;
}

int is_number(const char * str, int * num)//works
{
	int i, ret, neg;
	i = ret = neg = 0;
	char c;

	if (str[0] == '-') 
	{
		neg = 1;
		i++;
	}
	while(c = str[i])
	{
		if (c < '0' || c > '9') return 0;
		ret = ret*10 + c -'0';
		if (ret > MAXTODOS) return 0;
		i++;
	}

	*num = neg ? -ret : ret;
	return 1;
}

FILE * get_open_file(char * file_name)
{
	FILE *fp = fopen(file_name,"r+");
	if (!fp) fp = fopen(file_name,"w+");

	return fp;
}