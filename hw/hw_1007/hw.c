#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define SIZE 64

int main(int argc, char* argv[]){

	// 두 방 번호를 입력받고
	// 두 방의 투숙객을 교환
	// 모든 방의 투숙객을 출력

	// 파일 open
	
	int fd, n;
	int i = 1;
	char buf[SIZE];
	//memset(buf, 0, SIZE); // buf 배열 0으로 초기화	

	int room1 = atoi(argv[1]);
        int room2 = atoi(argv[2]);


	if(argc != 3 || room1 < 1 || room2 < 1){
		printf("usage : [room number1] [room number2]\neach room number starts from 1\n");
		exit(1);
	}

	fd = open("residents", O_RDWR);
	if(fd == -1){
		perror("open");
		exit(1);
	}	

	printf("(customer list)\n");
	printf("-----\n");
	while ((n = read(fd, buf, SIZE)) > 0) {
		if(buf != NULL){
			printf("Room %d: %s\n", i++, buf);
		}
	}
	printf("-----\n");
		
	char buf1[SIZE], buf2[SIZE];
	// seek
	lseek(fd, (room1 - 1) * SIZE, SEEK_SET);
	read(fd, buf1, SIZE);
 
	lseek(fd, (room2 - 1) * SIZE, SEEK_SET);
	read(fd, buf2, SIZE);
	
	//swap
	lseek(fd, (room1 - 1) * SIZE, SEEK_SET);
	write(fd, buf2, SIZE);

	lseek(fd, (room2 - 1) * SIZE, SEEK_SET);
	write(fd, buf1, SIZE);

	//offset 제자리
	lseek(fd, 0, SEEK_SET);
	
	//print	
        printf(" [ %d ] < --- > [ %d ]\n", room1, room2);
	printf("(customer list)\n");
	printf("-----\n");
	i = 1;
        while (n = read(fd, buf, SIZE) > 0) {
                if(buf != NULL){
                        printf("Room %d: %s\n", i++, buf);
                }
        }
        printf("-----\n");
	
	close(fd);
	return 0;
}

