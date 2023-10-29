/*Write a C program that a string as an argument and return all the files that begins with that name in the current directory.
For example > ./a.out foo will return all file names that begins with foo
*/
#include <stdio.h>
#include <dirent.h>
#include <string.h>

void listFilesStartingWith(const char*prefix)
	struct dirent *entry;
	DIR *dir= opendir(".");
	
	if(dir==NULL){
		perror("Error opening directory");
		return;
	}
	printf("Files starting with '%s'in the current directory;\n", prefix);
	
	while((entry = readdir(dir) !=NULL){
		if(strncmp(prefix, entry->d_name,strlen(prefx))==0){
			printf("%s\n", entry->d_name);
		}
	}
	closedier(dir);
}
int main(int argc, char *argv[])
{
	listFileStartingWith(argv[1]);
	return 0;
}
