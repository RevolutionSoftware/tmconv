#include <stdio.h>

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
	char name[256];
	Uint8 data[SZ];
	int col, row;
} Document;

Document doc;

/* Number to Character LUT */
Uint8
ntoc(Uint8 n)
{
	static const Uint8 clookup[95] = {
		/* clang-format off */
		0X20, 0X21, 0X22, 0X23, 0X24, 0X25, 0X26, 0X27, 0X28, 0X29,
		0X2A, 0X2B, 0X2C, 0X2D, 0X2E, 0X2F, 0X30, 0X31, 0X32, 0X33,
		0X34, 0X35, 0X36, 0X37, 0X38, 0X39, 0X3A, 0X3B, 0X3C, 0X3D,
		0X3E, 0X3F, 0X40, 0X41, 0X42, 0X43, 0X44, 0X45, 0X46, 0X47,
		0X48, 0X49, 0X4A, 0X4B, 0X4C, 0X4D, 0X4E, 0X4F, 0X50, 0X51,
		0X52, 0X53, 0X54, 0X55, 0X56, 0X57, 0X58, 0X59, 0X5A, 0X5B,
		0X5C, 0X5D, 0X5E, 0X5F, 0X60, 0X61, 0X62, 0X63, 0X64, 0X65,
		0X66, 0X67, 0X68, 0X69, 0X6A, 0X6B, 0X6C, 0X6D, 0X6E, 0X6F,
		0X70, 0X71, 0X72, 0X73, 0X74, 0X75, 0X76, 0X77, 0X78, 0X79,
		0X7A, 0X7B, 0X7C, 0X7D, 0X7E
		/* clang-format on */
	};
	if(n < 94)
		n = clookup[n];

	else
		return clookup[3];

	return n;
}
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
	d->col = 0;
	d->row = 0;
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
