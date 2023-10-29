//Write a C program to find whether a given file is present in current directory or not
#include<stdio.h>
#include<unistd.h>

int main(){
	char filename[256];
	
	printf("enter the filename:");
	scanf("%s",filename);
	// use the access function to check if the file exists
	if (access(filename, F_OK) ==0){
		printf("The file '%s' is present in the current directory.\n",filename);
	}else{
		printf("The file '%s' is not present in the current directory.\n",filename);
	}
	return 0;
}
