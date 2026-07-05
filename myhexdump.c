#include <stdio.h>
#include <ctype.h>

#define BYTES_PER_LINE 0x10
#define GROUP_LINE 0x8

int main(void)
{
	/* 0x10 + '/0' */
	unsigned char s[BYTES_PER_LINE + 1];
	/* c -> char, cc -> char counter, lc -> line counter */
	int c, cc = 0, lc = 0;
	while ((c = getchar()) != EOF) {
		if (cc == 0x0)
			printf("%08x  ", lc * BYTES_PER_LINE);

		printf("%02x ", c);
		/* Replace any non-printable char with '.' */
		s[cc] = isprint((unsigned char) c) ? c : '.';
		cc += 1;

		if (cc == GROUP_LINE)
			printf(" ");
		else if (cc == BYTES_PER_LINE) {
			s[BYTES_PER_LINE] = '\0';
			printf("|%s|\n", s);
			cc = 0;
			lc += 1;
		}
	}
	if (cc > 0) {
		/* Padding: each hex by takes 3 spaces (2 numbers and a space,
		 * like '65 '). At the end, we add 1 since we do an extra
		 * printf(" ") with GROUP_LINE, only if it wasn't printed yet */
		int pad = 3 * (BYTES_PER_LINE - cc) + (cc < GROUP_LINE ? 1 : 0);
		int pad2 = BYTES_PER_LINE - cc;
		/* Needs to finish the string with the remaining chars because
		 * if can print garbage from the string arrary */
		s[cc] = '\0';
		printf("%*s|%s%*s|\n", pad, "", s, pad2, "");
	}
	printf("%08x\n", lc * BYTES_PER_LINE + cc);

	return 0;
}
