#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]){

         char cwd[PATH_MAX];

        if(argc != 2) { // 명령행 인자 check
                fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);
                return 1;
        }

        DIR* dp;
        struct dirent *dent;

        int isExist = 0; // 파일 존재여부 플래그

        if((dp = opendir(".")) == NULL){ // 현재 디렉토리 open
                perror("opendir failed");
                return 1;
        }

        while((dent = readdir(dp))){
                // 두 문자열이 일치하는지 확인하기 위해
                // string.h ->  strcmp() 함수 사용
                // 외장 함수 없이 직접 구현하려면.. 복잡하니
                if(strcmp(dent->d_name, argv[1]) == 0){
                        isExist = 1; // 발견했으니 플래그 = true
                        break;       // while 문 stop
                }

        }


        if(isExist){
                printf("found !!\n");
        }else{
                printf("not found !!\n");
        }

        closedir(dp);

        return 0;

}
