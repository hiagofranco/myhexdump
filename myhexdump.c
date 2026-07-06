#include <stdio.h>
#include <ctype.h>

#define BYTES_PER_LINE 16

/*
 * Replace any non-printable char with '.'. Hexdump works like
 * that and this helps the last printed string to no be meesed
 * with '\n', '\t' and etc.
 */
void print_line_readable_text(unsigned char *buf, int cc)
{
	int pad = 3 * (BYTES_PER_LINE - cc) + (cc < BYTES_PER_LINE / 2 ? 1 : 0);

	printf("%*s |", pad, "");
	for (int i = 0; i < cc; i++)
		printf("%c", isprint((unsigned char) buf[i]) ? buf[i] : '.');
	printf("|\n");
}

void print_line_bytes(unsigned char *buf, int cc)
{
	for (int i = 0; i < cc; i++) {
		printf("%02x ", buf[i]);
		if (i == BYTES_PER_LINE / 2 - 1)
			printf(" ");
	}
}

void print_line_hex(int lc, int cc)
{
	printf("%08x ", lc * BYTES_PER_LINE + cc);
}
/*
 * Hexdump clone: This is for learning purposes.
 * Inputs a string, and the output will be equal to 'hexdump -C'.
 */
int main(void)
{
	/* +1 -> nul byte */
	unsigned char s[BYTES_PER_LINE + 1];
	/*
	 * c: char read. Needs to be int because of EOF (0xff)
	 * cc: char cout.
	 * lc: line count.
	 */
	int c, cc = 0, lc = 0;
	while ((c = getchar()) != EOF) {
		if (cc < BYTES_PER_LINE) {
			s[cc] = (unsigned char) c;
			cc += 1;
			continue;
		}
		s[BYTES_PER_LINE] = '\0';
		print_line_hex(lc, 0);
		print_line_bytes(s, cc);
		print_line_readable_text(s, cc);
		cc = 0;
		lc += 1;
	}
	if (cc > 0) {
		s[cc] = '\0';
		print_line_hex(lc, cc);
		print_line_bytes(s, cc);
		print_line_readable_text(s, cc);
	}
	print_line_hex(lc, 0);
	printf("\n");

	return 0;
}
