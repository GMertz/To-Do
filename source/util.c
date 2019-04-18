#include "util.h"
#include <stdio.h>/*for: printf, FILE, fopen*/
#include <string.h>/*for: strncpy, strlen*/
#include <stdlib.h>/*for: malloc*/
#include <unistd.h>/*for: getcwd, access*/
#include <inttypes.h>

#define HASHLEN 5

const char HEXDIGITS[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void error(char* str)
{
	printf("%s\n",str);
	exit(1);
}

char *concat(const char * source, const char * addend, const char delim)
{
	int len_s, len_a;
	len_s = len_a = 0;

	len_s = strlen(source);
	len_a = strlen(addend);

	char * ret = malloc(len_s + len_a+1+(delim));

	strncpy(ret,source,len_s);//copy source to ret
	if(delim){
		ret[len_s] = delim;
		len_s++;
	}
	strncpy(&ret[len_s],addend,len_a+1);//copy addend

	return ret;
}

char *substr(const char * source, int start, int end)
{
	int len = strlen(source), size = end-start;

	if (size > len || start < 0 || end > len-1 || size < 0)
		return 0;

	char *substr = malloc(size+1);

	for (int i = 0; i < size; ++i)
	{
		substr[i] = source[start+i];
	}

	substr[size] = 0;
	return substr;
}

char *get_local_path()
{
	char *buf = malloc(MAXPATHLEN);

	getcwd(buf,MAXPATHLEN);
	return buf;
}

//given a string, returns the minimum size string to hold source
char *trimmed_copy(const char * source)//maybe works
{
	int i = strlen(source);
	char *ret = malloc(i+1);
	strncpy(ret,source,i);
	ret[i] = 0;
	return ret;
}

int caseless_cmp(const char * a, const char * b)
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

int is_number(const char * str, int * num)
{
	int i, ret, neg;
	i = ret = neg = 0;
	char c;

	if (str[0] == '-') 
	{
		neg = 1;
		i++;
	}
	while (c = str[i])
	{
		if (c < '0' || c > '9') return 0;
		ret = ret*10 + c -'0';
		if (ret > MAXTODOS) return 0;
		i++;
	}

	*num = neg ? -ret : ret;
	return 1;
}

FILE * get_open_file(const char * file_name)
{
	FILE *fp = fopen(file_name,"r+");
	if (!fp) fp = fopen(file_name,"w+");

	return fp;
}

char *int_to_hex(int val)
{	
	char *ret_val = malloc(HASHLEN+1);
	if (!ret_val) return 0;

	int i = HASHLEN-1;
	while (i >= 0)
	{
		ret_val[i] = HEXDIGITS[val%16];
		val = val/16;
		i--;
	}
	ret_val[HASHLEN] = 0;
	return ret_val;
}
/*
	returns a hashed version of the current path
	all hashes will be length 5 hex
*/
char *get_hashed_path(const char *local_path, int offset)
{
	uint64_t val;
	int loc;
	val = loc = 1;
	char c;
	while((c = *(local_path++)) != 0)
	{
		val += loc * ABSOL(c-'A');
		loc++;
	}

	val %= (16*16*16*16*16);

	char *ret_val = int_to_hex(val);
	if(offset)
	{
		char *new_ret = concat(ret_val, int_to_hex(offset), 0);
		free(ret_val);
		return new_ret;
	}else 
		return ret_val;
}

char *get_effective_path(char *global_path, int mode)
{
	if(LOCAL == mode)
		return get_effective_path_local(global_path, 0);
	else
	{
		char *path = concat(global_path, "todo.txt", '\\');
		if(-1 == access(path,F_OK))
		{
			FILE *fp = fopen(path, "w");
			fputs(path,fp);
			fclose(fp);
		}
		return path;
	}
}

char *get_effective_path_local(char *global_path, int offset)
{
	char *ret_path = 0;
	char *local_path = get_local_path();
	char *hashed = get_hashed_path(local_path, offset);

	char *temp = concat(global_path, hashed,'\\');
	char *hashed_path = concat(temp, ".txt", 0);
	free(temp);
	
	if (-1 == access(hashed_path,F_OK))//file doesnt exist
	{	
		FILE *fp = fopen(hashed_path, "w");
		fputs(local_path,fp);
		fclose(fp);
		ret_path = malloc(MAXPATHLEN);
		strcpy(ret_path,hashed_path);
	}
	else
	{
		char buf[MAXPATHLEN];
		FILE *fp = fopen(hashed_path,"r");
		fgets(buf,MAXPATHLEN,fp);
		
		int i = strlen(buf);
		while(--i >= 0 && buf[i] != '\n')
			;
		if (buf[i] == '\n') buf[i] = 0;

		if(0 == strcmp(buf,local_path))
		{
			ret_path = malloc(MAXPATHLEN);
			strcpy(ret_path, hashed_path);
		}
	}

	free(hashed);
	free(local_path);
	free(hashed_path);
	return ret_path ? ret_path : get_effective_path_local(global_path, ++offset);
}
