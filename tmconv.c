#include <stdio.h>

#define NPRINTABLEASCII 96
#define FIRSTPRINTABLE 0x20
#define LASTPRINTABLE 0x7E
#define ISPRINTABLE(x) ((x) >= FIRSTPRINTABLE && (x) <= LASTPRINTABLE ? 1 : 0)

#define HOR 32
#define VER 16
#define PAD 2
#define SZ (HOR * VER * 16)

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef unsigned long Uint64;

typedef struct {
	int unsaved;
	int lut[NPRINTABLEASCII]; /* Look Up Table */
	char name[256];
	Uint8 data[SZ];
	int col, row;
} Document;

Document doc;

/* Helper Functions */

void
indexer(Document *d)
{
	int i;
	char c;
	for(i = 0, c = FIRSTPRINTABLE; c >= FIRSTPRINTABLE && c <= LASTPRINTABLE;
		++i, ++c)
		d->lut[i] = c;
}

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
	int i, j;
	for(i = 0; i < SZ; ++i) d->data[i] = 0x00;
	for(j = 0; j < NPRINTABLEASCII; ++j) d->lut[j] = 0x00;
	indexer(d);
	d->unsaved = 0;
	d->col = 0;
	d->row = 0;
	scpy(name, d->name, 256);
}

/* For debugging the indexer */
void
printindex()
{
	int i, j;
	char c;
	c = FIRSTPRINTABLE;
	i = 0;
	for(i = 0; i < NPRINTABLEASCII - 1 && c <= LASTPRINTABLE - 1;) {
		for(j = 0; j < 8 && i < NPRINTABLEASCII - 1 && c <= LASTPRINTABLE;
			++i, ++c)
			printf("(i[%01i], Character '%c')\n", i, doc.lut[i]);
	}
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
