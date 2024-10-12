#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
	DIR *dp;
	struct dirent *dent;
	struct stat statbuf;
	int count;
	//int find;
	int ind[256];

	if((dp = opendir(".")) == NULL){
		perror("opendir failed!\n");
		exit(1);
	}

	count = 0;
	while(dent = readdir(dp)){
		stat(dent->d_name, &statbuf);
		
		printf("dent->d_name : %s\n", dent->d_name);
		printf("Inode(dent) : %d\n", (int)dent->d_ino); 
		
		ind[count] = (int)statbuf.st_ino;
		printf("Inode(stat) : %d\n", (int)statbuf.st_ino);	
		printf("============================\n");
		count++;
		
	}
	closedir(dp);
	

	return 0;
}
