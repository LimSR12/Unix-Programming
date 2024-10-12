#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	struct stat statbuf;
	int x;
	
	// 명령행 인자 입력 데이터
	// ./hw1 g+w test.txt
	// 
	// argv[0] = ./hw1
	// argv[1] = g+w -> 권한처리 명령
	// argv[2] = filename -> 권한 처리할 대상 파일

	// 명령행 인지 check
	if (argc != 3) {
		printf("사용법: %s [권한] [파일명]\n", argv[0]);
		return 1;
   	}
	
	// 파일의 기존 권한 읽기
	if(stat(argv[2],&statbuf) == -1){
		perror("stat()");
		return 1;
	}

	// 기존 권한
	// statbuf.st_mode 에 저장된 권한 & 0777 -> u,g,o 권한만 추출되어 나옴
	
	printf("변경 전 권한: %o\n", statbuf.st_mode & 0777);

	// 명령행 인자로 전달된 명령 처리
	int i;
	for(i = 0; i < 3; i++){
		// 매 반복마다 x에 상수 저장 -> 매 반복 시작마다 reset 해줘야 함
		x = 0;
		switch(argv[1][i]){
			case '7': x |= S_IRWXU; break;
			case '6': x |= (S_IRUSR|S_IWUSR); break;
			case '5': x |= (S_IRUSR|S_IXUSR); break;
			case '4': x |= S_IRUSR; break; 
			case '3': x |= (S_IWUSR|S_IXUSR); break;
			case '2': x |= S_IWUSR; break;
			case '1': x |= S_IXUSR; break;
			case '0': x |= 0; break; 
			default: printf("%s는  잘못된 입력입니다\n", argv[1]); return 1;
		}

		// if() statbuf.st_mode |= x   ->  기존 권한과 or 연산
		// 기존 권한이 777 일 경우 000으로 변경할 수 없음
		// 따라서 변경하고자 하는 권한을 000으로 바꿔준 뒤 or 연산
		//
		// EX)
		// 111 101 101 -> 기존 권한
		// 000 111 111 -> ~0700
		// ----------------------
		// 000 101 101 -> 이제 여기에 x 와 or 수행
		// 101 000 000 
		// ----------------------
		// 101 101 101 -> 사용자 W 권한 삭제완료
		if(i == 0) statbuf.st_mode = (statbuf.st_mode & ~0700) | (x);
		if(i == 1) statbuf.st_mode = (statbuf.st_mode & ~0070) | (x>>3); 
		if(i == 2) statbuf.st_mode = (statbuf.st_mode & ~0007) | (x>>6);
	}
		
	// 권한 변경 적용
	if(chmod(argv[2], statbuf.st_mode) == -1){
		perror("권한 변경 오류");
		return 1;
	} 

	printf("변경 후 권한: %o\n", statbuf.st_mode & 0777);

	return 0;
}



















