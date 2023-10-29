/**
takes multiple files as Command Line Arguments and print their node number.
*/
#include<stdio.h>
#include<sys/stat.h>
#include<fnctl.h>
void main(int argc, char **argv){
	int i, ret;
	struct stat filestat;
	printf("Inode Numbers are ....\n");
	for(i=1; i<argc;i++){
		ret = stat(argv[i],&filestat);
		printf("%s :  ",argv[i]);
		if(ret < 0){
			printf("error reading filestat\n");
		} else{
			printf("%ld\n",filestat.st_ino);
		}
	}
