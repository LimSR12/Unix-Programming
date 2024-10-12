#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
     char *cwd;
     int fd;

     cwd = getcwd(NULL, BUFSIZ);
     printf("1.Current Directory: %s\n", cwd);

     fd = open("han", O_RDONLY); // readonly 로 열어주고 파일 디스크립터 리턴받음
     fchdir(fd);

     cwd = getcwd(NULL, BUFSIZ);
     printf("2.Current Directory: %s\n", cwd);

     close(fd); // open 후에 반드시 close
     free(cwd);
}


