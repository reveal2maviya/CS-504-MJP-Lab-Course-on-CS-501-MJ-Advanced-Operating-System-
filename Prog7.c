//Read the current directory and display the name of the files, no of files in current directory
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

int main(){
	struct dirent *entry;
	DIR *dp == NULL){
		perror("opendir");
		exit(1);
	}
	
	printf("Files in the current directory;\n");
	while((entry = readdir(dp)!=NULL){
		if(entry->d_type == DT_REG){//check if its a regular file		
			printf("%s\n",entry->d_name);
			fileCount++;
		}
	}
	printf("Number of files in the current directory: %d\n",fileCount);
	closedir(dp);
	return 0;
}
