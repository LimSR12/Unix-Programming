#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	
	char* cwd; // 현재 디렉토리 주소 기억
	char* new_cwd; // 새로 생성한 디렉토리 주소 기억	

	cwd = getcwd(NULL, BUFSIZ);

	printf("현재 디렉토리 경로 : %s\n",cwd);
	
	// 이동할 새로운 디렉토리 생성
	if(mkdir("new_dir", 0755) == -1){
		perror("mkdir failed!!");
		exit(1);
	}
	
	// 새로운 디렉토리로 이동
	printf("외부 디렉토리로 이동합니다\n");
	
	chdir("../");

	// 새로 생성한 디렉토리의 주소 확인
	new_cwd = getcwd(NULL, BUFSIZ);
	printf("현재 디렉토리 경로: %s\n", new_cwd);	
	
	// 새로운 디렉토리 작업중
	printf("외부 디렉토리 작업중\n");
	
	// 원래 디렉토리로 돌아감
	if(chdir(cwd) == -1){
		perror("chdir failed!!");
		exit(1);
	}	
	
	cwd = getcwd(NULL, BUFSIZ);

	printf("현재 디렉토리 경로 : %s\n", cwd);

	
	free(cwd);
	free(new_cwd);
	

	return 0;
}
