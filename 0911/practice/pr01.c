#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){	

	if(mkdir("dir1",0755) == -1){
		perror("dir1");
		exit(1);
	}

	if(mkdir("dir2",0755) == -1){
                perror("dir2");
                exit(1);
        }

	if(rmdir("dir1") == -1){
		perror("rmdir failed");
		exit(1);
	}
	
	if(rename("dir2", "testdir") == -1){
		perror("rename failed");
		exit(1);
	}	

	
	return 0;
}
