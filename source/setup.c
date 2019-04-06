#include <stdio.h>
#include <dir.h>
#include <stdlib.h>

#define MAXPATHLENGTH 300

char *concat(const char * source, const char * addend);
int compile(char *path);
void fix_it(char **path);

int main()
{
	printf("Setup will commence in the current working directory, ok? (y/n)\n");
	
	char *global_path;
	char c;
	while (1)
	{
		scanf("%c",&c);

		if (c == 'y')
		{
			char buf[MAXPATHLENGTH];
			global_path = concat(getcwd(buf,MAXPATHLENGTH),"\\todfiles");
			mkdir(global_path);
			compile(global_path);
			return 0;
		}
		else if (c == 'n') exit(0);
		else printf("enter y or n\n");
	}
}


char *concat(const char * source, const char * addend)
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

void fix_it(char ** path)
{
	int len = strlen(*path);
	char * new = malloc(MAXPATHLENGTH);
	int ni =0;
	for (int i = 0; i < len; ++i)
	{
		new[ni] = (*path)[i];
		ni++;
		if((*path)[i] == '\\')
		{
			new[ni] = '\\';
			ni++;

			if(ni == MAXPATHLENGTH-1)
			{
				printf("path size too large!\n");
				exit(0);
			}
		}
	}
	new[ni] = 0;
	*path = new;
}

int compile(char *path)
{
	fix_it(&path); 
	system("cd ..\\source");
	char *command = concat("gcc driver.c commands.c ll.c todo.c util.c -o todo.exe -DGLOBALPATH=\\\"",path);
	command = concat(command,"\\\"");
	system(command);
	system("mv todo.exe ..\\bin");
	printf("finished!\n");
	return 1;
}