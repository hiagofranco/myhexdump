#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
 * Hexdump clone: This is for learning purposes.
 * Inputs a string, and the output will be equal to 'hexdump -C'.
 */

#define BYTES_PER_LINE 16

/*
 * Replace any non-printable char with '.'. Hexdump works like
 * that and this helps the last printed string to no be meesed
 * with '\n', '\t' and etc.
 */
void print_line_readable_text(unsigned char *buf, int cc)
{
	int i;
	int pad = 3 * (BYTES_PER_LINE - cc) + (cc < BYTES_PER_LINE / 2 ? 1 : 0);

	printf("%*s |", pad, "");
	for (i = 0; i < cc; i++)
		printf("%c", isprint((unsigned char) buf[i]) ? buf[i] : '.');
	printf("|\n");
}

void print_line_bytes(unsigned char *buf, int cc)
{
	int i;
	for (i = 0; i < cc; i++) {
		printf("%02x ", buf[i]);
		if (i == BYTES_PER_LINE / 2 - 1)
			printf(" ");
	}
}

void print_line_hex(int lc, int cc)
{
	printf("%08x  ", lc * BYTES_PER_LINE + cc);
}

void print_line(unsigned char *buf, int lc, int cc)
{
	print_line_hex(lc, 0);
	print_line_bytes(buf, cc);
	print_line_readable_text(buf, cc);
}

int main(void)
{
	unsigned char s[BYTES_PER_LINE];
	unsigned char last[BYTES_PER_LINE];
	/*
	 * c: char read. Needs to be int because of EOF (0xff)
	 * cc: char cout.
	 * lc: line count.
	 */
	int c, cc = 0, lc = 0;
	int asterisk_printed = 0;
	while ((c = getchar()) != EOF) {
		if (cc < BYTES_PER_LINE) {
			s[cc] = (unsigned char) c;
			cc += 1;
			continue;
		}
		/*
		 * If equals to the last buffer, we want to print an '*'
		 * instead.
		 */
		if (memcmp(s, last, BYTES_PER_LINE) == 0) {
			if (!asterisk_printed) {
				printf("*\n");
				asterisk_printed = 1;
			}
		}
		else {
			print_line(s, lc, cc);
			asterisk_printed = 0;
		}
		memcpy(last, s, BYTES_PER_LINE);
		/*
		 * At this stage, there is one 'c' read that cannot be lost,
		 * since we have a if on the beginning of the while loop.
		 * Therefore, we need to store this 'c' so we do not lose it.
		 */
		s[0] = (unsigned char) c;
		cc = 1;
		lc += 1;
	}

	if (cc > 0)
		print_line(s, lc, cc);

	print_line_hex(lc, cc);
	printf("\n");

	return 0;
}
