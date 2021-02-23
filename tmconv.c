#include <stdio.h>

int
error(char *msg, const char *err)
{
	printf("Error %s: %s\n", err, msg);
	return 1;
}

int
main(int argc, char *argv[])
{
	FILE *fp;
	char *outnam; /* Base for output-filename */

	if(argc < 2) {
		printf("Usage: %s formated.txt [optional base for outputnames]\n", argv[0]);
		return 0;
	}
	if(!(fp = fopen(argv[1], "r")))
		return error("Cannot open file", "Invalid inputfile");

	outnam = (argc >= 3) ? argv[2] : "output";

	return 0;
}
