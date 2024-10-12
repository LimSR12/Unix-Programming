#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

main() {

        if (mkdir("han", 0755) == -1) {
                perror ("han");
                exit(1);
        }

        if (mkdir("bit", 0755) == -1) {
                perror ("bit");
                exit(1);
        }

        if (rmdir("bit") == -1) {
                perror("bit");
                exit(1);
        }
}


