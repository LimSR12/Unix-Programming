#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "test.txt"

int main(void)
{
	int fd = open(FILENAME, O_CREAT|O_RDWR, 0644);	

	umask(0);
	unlink(FILENAME);
	fd = open(FILENAME, O_CREAT|O_RDWR, 0644);	


	unlink(FILENAME);
	umask(0321);
	fd = open(FILENAME, O_CREAT|O_RDWR, 0644);

	unlink(FILENAME);
	umask(0444);
	fd = open(FILENAME, O_CREAT|O_RDWR, 0755);
	return 0;
}

