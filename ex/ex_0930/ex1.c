#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 512

int main(int argc, char* argv[]){
	//./ex test.txt test.bak
	int fd, fd_cp;
	char buf[SIZE];

	fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		perror("open argv[1]");
		exit(1);
	}

	//fd_cp = open(argv[2], O_RDWR);
	fd_cp = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(fd_cp == -1) {
		perror("open argv[2]");
		exit(1);
	}
	
	int n;
	while((n = read(fd, buf, 7)) > 0){
		// read( ) 가 실패하면 -1, 내용이 끝나면 0 return
		if(write(fd_cp, buf, n) != n) perror("write");
		if(n == -1) perror("read"); 
	}

	close(fd);
	close(fd_cp);
	
	return 0;
}

