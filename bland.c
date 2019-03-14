//https://www.codechef.com/problems/COINS

#include <stdio.h>
#include <stdlib.h>

unsigned **cache;

unsigned process_value(unsigned value, unsigned twos_level, unsigned threes_level) {
	if (value < 12) {
		return value;
	} else if (value == 12) {
		return 13;
	}
    
    unsigned *cached = *(cache + twos_level) + threes_level;
    
    if (*cached != 0) {
        return *cached;
    }
	
	
	unsigned from_half = process_value(value / 2, twos_level + 1, threes_level);
	unsigned from_third = process_value(value / 3, twos_level, threes_level + 1);
	unsigned from_quarter = process_value(value / 4, twos_level + 2, threes_level);

	unsigned subtotal = from_half + from_third + from_quarter;
    
    unsigned result = (subtotal > value) ? subtotal : value;
    
    *cached = result;
    
    return result;
}

int main(int argc, const char **argv) {
	FILE *input;
	unsigned n;

	if (argc > 1) {
		input = fopen(*(argv + 1), "r");
	} else {
		input = stdin;
	}

	fscanf(input, "%u", &n);
    
    cache = calloc(29, sizeof(unsigned*));
    int i;
    
    for (i = 0; i < 29; i++) {
        *(cache + i) = calloc(19, sizeof(unsigned));
    }

	unsigned result = process_value(n, 0, 0);

	if (input != stdin) {
		fclose(input);
	}

	printf("%u\n", result);
	
	return 0;
}
