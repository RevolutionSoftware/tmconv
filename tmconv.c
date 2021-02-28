#include <stdio.h>

#define HOR 32
#define VER 16
#define PAD 2
#define SZ (HOR * VER * 16)

#define FIRSTPRINTABLE 32
#define LASTPRINTABLE 127
#define NPRINTABLEASCII 96

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef unsigned long Uint64;

typedef struct {
	int unsaved;
	char name[256];
	Uint8 data[SZ];
} Document;

Document doc;

/* Helper Functions */
int
error(char *msg, const char *err)
{
	printf("Error %s: %s\n", msg, err);
	return 1;
}

char *
scpy(const char *src, char *dst, int len)
{
	int i = 0;
	while((dst[i] = src[i]) && i < len - 2) i++;
	dst[i + 1] = '\0';
	return dst;
}

int
slen(const char *src)
{
	int i = 0;
	while(src[i++] != '\0')
		;
	return i;
}

void
makedoc(Document *d, char *name)
{
	int i;
	for(i = 0; i < SZ; ++i) d->data[i] = 0x00;
	d->unsaved = 0;
	scpy(name, d->name, 256);
}

int
main(int argc, char *argv[])
{
	FILE *fp;
	char *outnam; /* Base for output-filename */

	if(argc < 2) {
		printf("Usage: %s formated.txt [optional: base for outputnames]\n",
			argv[0]);
		return 0;
	}
	if(!(fp = fopen(argv[1], "r")))
		return error("Invalid inputfile", "Cannot open file");

	outnam = (argc >= 3) ? argv[2] : "output";
	makedoc(&doc, outnam);

	return 0;
}
