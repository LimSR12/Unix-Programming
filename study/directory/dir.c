#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char* argv[]){

	// 디렉토리 생성
	if(mkdir("test_directory",0755) == -1){
		perror("mkdir");
		exit(1);
	}
	
	// 디렉토리 변경
	if(chdir("test_directory/") == -1){
		perror("chdir");
		exit(1);
	}	

	// 현재 경로 출력
	char* cwd;
	char buffer[512];
	
	cwd = getcwd(buffer, sizeof(buffer)); 
	// getcwd는 buffer에 경로 저장해주는 역할
	// 이때 getcwd 함수는 현재 경로를 buffer 에 저장해줌
	// buffer 는 스택에 할당된 메모리이므로 따로 메모리 해제 필요없음
	// 만약 cwd = getcwd(NULL, 512); 와 같이 사용했다면, getcwd 함수는 malloc 으로 
	// 동적 할당받아 저장하고 시작 포인터를 cwd 에 반환할 것 -> 반드시 free 필요!!

	if(cwd == NULL) printf("getcwd error");
	
	printf("%s\n", buffer);		

	// 디렉토리 삭제
	chdir("../");
	if(rmdir("test_directory") == -1 ){
		perror("rmdir");
		exit(1);
	}
	
	// dirent이용해 디렉토리 열고 닫기
	DIR* dp; // 디렉토리를 열고 해당 디렉토리를 가리키는 스트림 포인터

	if((dp = opendir(".")) == NULL){
		perror("opendir");
		exit(1);
	}
	
	struct dirent* dent;
	char* newcwd = get_current_dir_name();
	
	// dp가 가리키는 디렉토리부터 열어서 내용 읽고 dent 에 저장
	while((dent = readdir(dp)) != NULL){
		printf("%s/%s\n", newcwd, dent->d_name);
	}
	
		
	// 만약 여기서 newcwd 를 free 시켜주지 않고 아래에서 재사용 한다면 어떻게 될까
	// 위에서 동적으로 할당 받은 메모리 주소는 사라지고, newcwd에는 새로운 메모리 address 주소
	// 그럼 처음 가리키던 메모리의 주소는 다시 찾아서 해제시킬 방법이 없음
	//  -> memory leak ( 메모리 누수)
	free(newcwd);
	closedir(dp);

	printf("----------------------\n");
	// 현재 디렉토리에서 명령행 인자로 받은 문자열과 일치하는 디렉토리
	// 있는지 확인하고 결과 출력
	
	if(argc != 2){
		printf("usage : [%s] [찾을 하위 디렉토리명]", argv[0]);
		exit(1);
	}
	dp = opendir(".");
	if(dp == NULL){
		perror("readdir");
		exit(1);
	}
	
	long pos; // 찾으려는 디렉토리 위치 기억
	int isExist = 0;
	while((dent = readdir(dp)) != NULL){
		if(strcmp(argv[1], dent->d_name) == 0){
			printf("디렉토리  [%s]가 존재합니다.\n : %s\n", argv[1], dent->d_name);
			isExist = 1;
			break;
		}
	}
		
	if(isExist){ // 파일이 존재하면 해당 위치로 이동, 경로 출력
		//seekdir(dp, pos); // pos 로 dp 이동
		chdir(dent->d_name);
		newcwd = get_current_dir_name();
		printf("현재 위치 : %s/\n", cwd);	
	}else{
		printf("Not Found\n");
	}
	
	


	free(newcwd);
	closedir(dp);
	return 0;
}
