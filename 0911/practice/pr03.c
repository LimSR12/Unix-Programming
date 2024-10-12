#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>


int main(){
	
	// 디렉토리가 비어있는지 확인하고 디렉토리가 비어있으면 메시지 출력 후 삭제
	
	DIR* dp;
	struct dirent *dent;
	
	char cwd[PATH_MAX];

	if((dp = opendir(".")) == NULL){
		perror("opendir failed");
		exit(1);
	}	

	while((dent = readdir(dp))){
                //printf("dp : %s || ",dp);
                printf("dent->d_name : %s\n",dent->d_name);

		//if(dent->d_name[0] == '.'){
		//	printf("%s\n",dp);
		//	printf("%s\n",dent->d_name);	
		//}
	
	}

	

	return 0;
}
