#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 100


int main(){

        int fd1[2], fd2[2];
        pid_t pid;
        char msg[MSG_SIZE], inmsg[MSG_SIZE];

        if(pipe(fd1) == -1 || pipe(fd2) == -1){
                perror("pipe");
                exit(1);
        }

        if((pid = fork()) == 0){
                // child process
                close(fd1[1]);
                close(fd2[0]);

                //printf("------------------------------\n");
                while(1){
                        // 부모로부터 메시지 receive
                        int msg_len = read(fd1[0], inmsg, sizeof(inmsg));
                        if(msg_len > 0){
                                inmsg[msg_len] = '\0';
                                printf("child recieved : %s", inmsg);
                        }

                        // 사용자로부터 답장할 메시지 입력받음
                        printf("child >> ");
                        fgets(inmsg, sizeof(inmsg), stdin);

                        printf("------------------------------\n");
                        // 부모에게 메시지 send
                        write(fd2[1], inmsg, strlen(inmsg));

                }
        }else if(pid > 0){
                // parent process
                close(fd1[0]);
                close(fd2[1]);

                while(1){
                        // 사용자로부터 메시지 입력받음
                        printf("parent >> " );
                        fgets(msg, sizeof(msg), stdin);

                        printf("------------------------------\n");
                        // child 프로세스에게 메시지 전송
                        write(fd1[1], msg, strlen(msg));

                        // child 로부터 받은 메시지 출력
                        int msg_len = read(fd2[0], msg, sizeof(msg));
                        if(msg_len > 0){
                                msg[msg_len] = '\0';
                                printf("parent received : %s");
                        }

                }
        }else{
                // pid < 0 -> fork() 에러
                perror("fork");
                exit(1);
        }

        return 0;
}
