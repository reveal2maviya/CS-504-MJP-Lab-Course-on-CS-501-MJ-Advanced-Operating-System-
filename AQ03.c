/*
Write a C program to find file properties such as inode number,number of hard link,
File permissions, File size, File access and modification time and so on of a given file using stat() system call.
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>

int main(int argc, char *argv[])
{
	
	
	const char *filename = argv[1];
	struct stat file_stat;
	
	printf("File Information for: %s\n",filename);
	printf("Inode number: %ld\n",(long)file_stat.st_ino);
	printf("Number of hard links: %ld\n",(long)file_stat.st_ino);
	printf("File size: %ld bytes\n",(long)file_stat.st_size);
	printf("File permissions;");
	printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
	printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
	printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
	printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
	printf("\n");
	
	printf("Last access time: %s",ctime(&file_stat.st_atime));
	printf("Last modification time: %s", ctime(&file_stat.st_mtime));
	
	return 0;
	}