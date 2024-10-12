#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *name[] = {
        "David Hutchison",
        "Takeo Kanade",
        "Josef Kittler",
        "John M. Kleinberg",
        "Friedemann Mattern",
        "John C. Mitchell",
        "Moni Naor",
        "Oscar Nierstrasz",
        "C. Pandu Rangan",
        "Bernhard Steffern",
        "Madhu Sudan",
        "Demetri Tygar",
        NULL
};

int
main() {

        int i, out;
        char wbuf[64];

        memset(wbuf, 0, sizeof(wbuf));

        if ((out = open("residents", O_CREAT|O_RDWR, 0644)) < 0) {
                perror("no testdata");
                exit(1);
        }

        for (i=0; name[i]!=NULL; i++) {
		size_t len = strlen(name[i] + 1);
		memcpy(wbuf, name[i], len);
                write(out, wbuf, sizeof(wbuf));
		printf(" %s %d %s\n", wbuf, i+1, name[i]);
                memset(wbuf, 0, sizeof(wbuf));
        }

        close (out);

}


