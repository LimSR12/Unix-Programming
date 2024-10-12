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
		perror("파일을 열 수 없습니다");
		return 1;
	}

	// 기존 권한
	// statbuf.st_mode 에 저장된 권한 & 0777 -> u,g,o 권한만 추출되어 나옴
	
	printf("변경 전 권한: %o\n", statbuf.st_mode & 0777);

	// 명령행 인자로 전달된 명령 처리
	switch(argv[1][0]){

		case 'u':
			switch(argv[1][2]){
				case 'r': x = S_IRUSR;break;
				case 'w': x = S_IWUSR;break;
				case 'x': x = S_IXUSR;break;	
				default: printf("잘못된 사용자 권한입니다.\n"); return 1;
			}
			break;
		case 'g':
			switch(argv[1][2]){
				case 'r': x = S_IRGRP; break;
				case 'w': x = S_IWGRP; break;
				case 'x': x = S_IXGRP; break;
				default: printf("잘못된 그룹 권한입니다.\n"); return 1;
			}
			break;
		case 'o':
			switch(argv[1][2]){
				case 'r': x = S_IROTH; break;
				case 'w': x = S_IWOTH; break;
				case 'x': x = S_IXOTH; break;
				dafault: printf("잘못된 기타 권한입니다.\n"); return 1;
			}
			break;
		default: 
			printf("잘못된 권한 유형입니다."); return 1;
	}
	

	// 권한 변경 처리
	if(argv[1][1] == '+'){
		// x에 저장된 상수와 or 연산 통해 권한 추가
		statbuf.st_mode |= x;
	}
	else if(argv[1][1] == '-'){
		// x에 저장된 상수를 반전시켜 and 연산 통해 권한 삭제
		//
		// ex) 그룹 사용자의 작성권한 삭제
		// 111 011 001 -> 기존 권한
		// 000 010 000 -> S_IWGRP
		// 111 101 111 -> ~(S_IXGRP)
		//
		// AND 연산 결과
		// 111 011 001
		// 111 101 111
		// -------------
		// 111 001 001 -> 기존 권한에서 그룹사용자 작성권한 삭제됨  
		//
		statbuf.st_mode &= ~(x);
	}
	else{
		printf("잘못된 입력입니다.");
	}

	// 권한 변경 적용
	if(chmod(argv[2], statbuf.st_mode) == -1){
		perror("권한 변경 오류");
		return 1;
	} 

	printf("변경 후 권한: %o\n", statbuf.st_mode & 0777);

	return 0;
}



















