#include <stdio.h>
#include <ctype.h>

#define BYTES_PER_LINE 0x10
#define GROUP_LINE 0x8

/*
 * Hexdump clone: This is for learning purposes.
 * Inputs a string, and the output will be equal to 'hexdump -C'.
 */
int main(void)
{
	/*
	 * String to be printed at the end of the line. I has exactly the
	 * number of bytes printed per line plus the nul byte.
	 */
	unsigned char s[BYTES_PER_LINE + 1];
	/*
	 * c: char read. Needs to be int because of EOF (0xff)
	 * cc: char cout.
	 * lc: line count.
	 */
	int c, cc = 0, lc = 0;
	while ((c = getchar()) != EOF) {
		/*
		 * Start of line: '00000000', '00000010' and so on...
		 */
		if (cc == 0)
			printf("%08x  ", lc * BYTES_PER_LINE);

		printf("%02x ", c);

		/*
		 * Replace any non-printable char with '.'. Hexdump works like
		 * that and this helps the last printed string to no be meesed
		 * with '\n', '\t' and etc.
		 */
		s[cc] = isprint((unsigned char) c) ? c : '.';
		cc += 1;

		/*
		 * We want to divide the printed string with 16 bytes length
		 * with two groups os 8 bytes.
		 */
		if (cc == GROUP_LINE)
			printf(" ");
		/*
		 * If we reach the end of the 16 bytes, we need to go to the
		 * next line. Therefore, we print the string with ASCII chars
		 * and go to the next one.
		 */
		else if (cc == BYTES_PER_LINE) {
			s[BYTES_PER_LINE] = '\0';
			printf(" |%s|\n", s);
			cc = 0;
			lc += 1;
		}
	}
	/*
	 * After reading all the bytes, if there are any bytes that did not
	 * fill up until the last 16 bytes, we need to print them with some
	 * padding to do not mess with the output.
	 *
	 * Example:
	 * 00000010  67 6f 20 44 65 20 46 72  61 6e 63 6f 2c 20 48 65  |go De Franco, He|
	 * 00000020  6c 6c 6f 20 3a 29 0a                              |llo :).|
	 * 00000027
	 */
	if (cc > 0) {
		/*
		 * Padding: each hex by takes 3 spaces (2 numbers and a space,
		 * like '65 '). At the end, we add 1 since we do an extra
		 * printf(" ") with GROUP_LINE, only if it wasn't printed yet.
		 */
		int pad = 3 * (BYTES_PER_LINE - cc) + (cc < GROUP_LINE ? 1 : 0);
		int pad2 = BYTES_PER_LINE - cc;
		/*
		 * Need to finish the string with the remaining chars because
		 * it can print garbage from the string arrary
		 */
		s[cc] = '\0';
		printf("%*s |%s%*s|\n", pad, "", s, pad2, "");
	}
	printf("%08x\n", lc * BYTES_PER_LINE + cc);

	return 0;
}
