/*
 * Program to experiment with timing analysis of
 * binary exponentiation.
 *
 * (C) 2013 Henry de Valence <hdevalence@hdevalence.ca>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*
 * Compute x^a mod p. This is not guaranteed to be 
 * correct unless x, p < 2^16.
 */
uint32_t binary_exp_c(uint32_t x, uint32_t a, uint32_t p)
{
	uint32_t r = 1;
	uint32_t y = x;
	while (a>1) {
		if (a & 1)
			r = (r*y) % p;
		y = (y*y) % p;
		a >>= 1;
	}
	return (r*y) % p;
}

#if 0
/*
 * ARM assembler implementation of binary_exp_c.
 */
uint32_t binary_exp_asm(uint32_t x, uint32_t a, uint32_t p)
{
	uint32_t r, tmp_div;
	__asm__ __volatile__(
	"mov	%[r], #1"		"\n\t" /* Set r = 1 */
	"binary_exp_loop:"		"\n\t" /* Begin loop */
	"cmp	%[a], #1"		"\n\t" /* if a <= 1, end */
	"ble	loop_end"		"\n\t" 
	"tst	%[a], #1"		"\n\t" /* If a odd then */
	"beq	skip_odd"		"\n\t"
	"mul	%[r], %[r], %[x]"	"\n\t"
	"udiv	%[td], %[r], %[p]"	"\n\t"
	"mls	%[r], %[td], %[p],%[r]"	"\n\t" /* r *= x mod p */
	"skip_odd:"			"\n\t"
	"mul	%[x], %[x], %[x]"	"\n\t"
	"udiv	%[td], %[x], %[p]"	"\n\t"
	"mls	%[x], %[td], %[p],%[x]"	"\n\t" /* x *= x mod p */
	"lsrs	%[a], %[a], #1"		"\n\t" /* divide exp by 2 */
	"beq	loop_end"		"\n\t" /* break if exp=0 */
	"b	binary_exp_loop"	"\n\t"
	"loop_end:"			"\n\t"
	"mul	%[x], %[r], %[x]"	"\n\t"
	"udiv	%[td], %[x], %[p]"	"\n\t"
	"mls	%[x], %[td], %[p],%[x]"	"\n\t" /* x *= r mod p */
	: [x]"=r"(x), 
	  [a]"=r"(a),
	  [r]"=r"(r),
	  [td]"=r"(tmp_div)
	: "0"(x),
	  "1"(a),
	  [p]"r"(p)
	: "cc");
	return x;
}
#endif

int main(int argc, char** argv)
{
	uint32_t x = atoi(argv[1]);
	uint32_t a = atoi(argv[2]);
	uint32_t p = atoi(argv[3]);
	for(int i = 0; i < 100000000; ++i) {
		binary_exp_c(x,a,p);
	}
    /*
	printf("%d\n", binary_exp_c(x,a,p));
	printf("%d\n", binary_exp_asm(x,a,p));
    */
	return 0;
}

