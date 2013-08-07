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

int __attribute__((optimize("O0"))) main(int argc, char** argv)
{
	uint32_t x = atoi(argv[1]);
	uint32_t a = atoi(argv[2]);
	uint32_t p = atoi(argv[3]);
	uint32_t y;
	for(int i = 0; i < 100000000; ++i) {
		y = binary_exp_c(x,a,p);
	}
	printf("%d^%d (mod %d) = %d\n", x,a,p,y);
	return 0;
}

