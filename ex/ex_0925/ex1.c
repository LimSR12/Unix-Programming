#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
	
	int n = 0;
	char buf[BUFSIZ];	
	char symname[BUFSIZ];	

	while(argv[1][n] != '.') {
		buf[n] = argv[1][n];
		n++;
	}
	buf[n] = '\0';

	printf("buf: %s\n", buf);
		
	//symlink(buf, "buf.sym");
	
	sprintf(symname, "%s.sym", buf);
	printf("symname: %s\n", symname);

	symlink(argv[1], symname);
	
	return 0;
}
