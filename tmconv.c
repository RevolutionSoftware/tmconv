#include <stdio.h>

typedef unsigned char Uint8;

typedef struct {
	char name[256];
	Uint8 *data;
} Document;

int
error(char *msg, const char *err)
{
	printf("Error %s: %s\n", msg, err);
	return 1;
}

int
main(int argc, char *argv[])
{
	FILE *fp;
	char *outnam; /* Base for output-filename */

	if(argc < 2) {
		printf("Usage: %s formated.txt [optional: base for outputnames]\n", argv[0]);
		return 0;
	}
	if(!(fp = fopen(argv[1], "r")))
		return error("Invalid inputfile", "Cannot open file");

	outnam = (argc >= 3) ? argv[2] : "output";

	return 0;
}
