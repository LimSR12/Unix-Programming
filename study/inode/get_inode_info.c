#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main(){
	struct stat statbuf; // stat 함수를 통해 metadata 받아올 구조체
	const char* path = "get_inode_test.txt";

	if(stat(path, &statbuf) == -1){
		perror("stat");
		exit(1);
	}

	printf("\npath = %s\n", path);

	printf("inode 번호: %d\n", statbuf.st_ino);

	return 0;
}	
