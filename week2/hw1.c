#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>


int main(int argc, char *argv[]){

         char cwd[PATH_MAX];

        if(argc != 2) {
                fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);
                return 1;
        }

        if(mkdir(argv[1], 0755) == -1){

                perror("mkdir failed");
                return 1;

        }

        if(chdir(argv[1]) == -1) {
                perror("chdir failed");
                return 1;
        }

        if(getcwd(cwd, sizeof(cwd)) == NULL){

                perror("getcwd failed");
                return 1;
        }


        char* cur = getcwd(NULL, BUFSIZ);

        printf("current directory : %s\n", cur);

        free(cur);

        return 0;

}
