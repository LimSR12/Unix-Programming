#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int fd, n;
	
	off_t start, cur;
	char buf[256];

	fd = open("test.txt", O_CREAT);
	if(fd == -1){
		perror("open");
		exit(1);
	}

	start = lseek(fd, 0, SEEK_SET); // start에는 파일의 시작점
	
	while((n = read(fd, buf, 1)) > 0){
		write(1, buf, 1);
		start = lseek(fd, 1, SEEK_CUR);
	}
	
	close(fd);
	return 0;
}
