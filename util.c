#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "commands.h"


/*void  unary_commands[] = {};
(void*) binary_commands[] = {};*/
//how to do array of fnction pointer?



void error(char* str)
{
	printf("Error: %s\n",str);
	safe_exit();
}

void safe_exit()
{
	exit(0);
}

char* concat(char * source, char * addend)//works
{
	int len_s, len_a;
	len_s = len_a = 0;

	while(source[++len_s]);//len- '\0'
	while(addend[len_a++]);//len

	char * ret = malloc(len_s + len_a);

	strncpy(ret,source,len_s);//copy source to ret
	strncpy(&ret[len_s],addend,len_a);//copy addend
	return ret;
}

char * get_dir_name()//works
{
	char buf[MAXPATHLEN], c;
	int len = 0, end, dif;

	getcwd(buf,MAXPATHLEN);

	while(buf[++len]);

	end = len;

	while(buf[--end] != '\\');

	dif = len-end;

	char * ret = malloc(dif);

	end++;

	for (int i = 0; i < dif; i++){
		ret[i] = buf[end+i];
	}

	ret[dif-1] = 0;
	return ret;
}

//given a string, returns the minimum size string to hold source
char * trimmed_copy(const char * source)//maybe works
{
	int i = 0;
	while(source[++i]);
	char * ret = malloc(i);
	strncpy(ret,source,i);
	ret[i-1] = 0;
	return ret;
}

int caseless_cmp(const char * a, const char * b)//works
{
	if (!a || !b) return 0;
	
	while (*a && *b)
	{
		int dif = *a - *b;
		if(dif != 32 && dif != 0 && dif != -32) return 0;
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

	if(str[0] == '-') 
	{
		neg = 1;
		i++;
	}
	while(c = str[i])
	{
		if(c < '0' || c > '9') return 0;
		ret = ret*10 + c -'0';
		i++;
	}

	*num = neg ? -ret : ret;
	printf("num:%d\n",num );
	return 1;
}

int is_string(const char * str)//works
{
	int i = 0;
	char c;
	while(c = str[i]){
		if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
			return 0;
		i++;
	}
	printf("%s is valid\n",str);
	return 1;

}

FILE * get_open_file(char * file_name, char * mode)
{
	FILE *fp = fopen(file_name,"r+");
	if(!fp) fp = fopen(file_name,"w+");

	return fp;
}

void serialize_todos(ll_node_t todos, char* file_name)
{
	printf("%s\n",file_name );
	return;
	FILE *fp = fopen(file_name, "w");
	while(todos.next)
	{
		fputs(todos.val,fp);
		fputc('\n',fp);
	}

	fputs(todos.val,fp);
	fclose(fp);
}