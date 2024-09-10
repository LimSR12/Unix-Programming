#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

int main(){


        DIR* dp; // 디렉토리 포인터

        struct dirent *dent; // 디렉토리 내용 읽기

        //dp = opendir(".");

        if((dp = opendir(".")) == NULL){
                perror("opendir failed");
                return 1;
        }

        while((dent = readdir(dp))){
                if(dent->d_name[0] != '.'){
                        printf("%s\n", dent->d_name);
                }
        }

        closedir(dp);

        return 0;
}
