#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    struct stat statbuf;

    chmod("test.txt", S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);

    stat("test.txt", &statbuf);
    printf("1.Mode = %o\n", (unsigned int)statbuf.st_mode);
    statbuf.st_mode |= S_IWGRP;
    statbuf.st_mode &= ~(S_IROTH);
    chmod("test.txt", statbuf.st_mode);

    stat("test.txt", &statbuf);
    printf("2.Mode = %o\n", (unsigned int)statbuf.st_mode);
}

