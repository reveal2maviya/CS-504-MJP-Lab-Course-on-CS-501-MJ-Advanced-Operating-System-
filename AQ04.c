/*
print the type of file where file name accepted througgh Command Line.
*/
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
void main(int argc, char **argv){
	if(argc < 2)
	{
		printf("No file name passed\n");
		exit(0);
		}
		struct stat filestat;
		
		if (S_ISREG(filestat.st_mode)){
			printf("%s is a regular file\n", argv[1]);
		}
		else if (S_ISDIR(filestat.st_mode)){
			printf("%s is a directory\n", argv[1]);
		}
		else if (S_ISCHR(filestat.st_mode)){
			printf("%s is a character device\n", argv[1]);
		}
		else if (S_ISBLK(filestat.st_mode)){
			printf("%s is a block device\n", argv[1]);
		}
		else if (S_ISFIFO(filestat.st_mode)){
			printf("%s is a named pipe\n", argv[1]);
		}
		else if (S_ISLNK(filestat.st_mode)){
			printf("%s is a symbolic link\n", argv[1]);
		}
		else if (S_ISSOCK(filestat.st_mode)){
			printf("%s is a socket\n", argv[1]);
		}
	}
