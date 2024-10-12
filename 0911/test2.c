#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
     char *cwd;
     char wd1[BUFSIZ];
     char wd2[10];

     getcwd(wd1, BUFSIZ);
     printf("wd1 = %s\n", wd1); // wd1 이라는 버퍼를 지정하여 버퍼에 받음

     cwd = getcwd(NULL, BUFSIZ);
     printf("cwd1 = %s\n", cwd); // 버퍼를 NULL로 전달하고 directory pointer를 return 받음
     free(cwd);

     cwd = getcwd(NULL, 0);
     printf("cwd2 = %s\n", cwd); // pointer 리턴받는데 버퍼 사이즈가 0
     free(cwd);

     if(getcwd(wd2, 10) == NULL) {
         perror("getcwd");
         exit(1);
     }
}


