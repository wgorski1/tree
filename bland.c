//https://www.codechef.com/problems/COINS

#include <stdio.h>
#include <stdlib.h>

struct coin;

typedef struct coin *coin;

struct coin {
	unsigned val;
	unsigned dollars;
	coin half;
	coin third;
	coin quarter;
};

coin create_coin(unsigned val) {
	coin acoin = malloc(sizeof(struct coin));
        acoin->val = val;
        acoin->dollars = 0;
        acoin->half = acoin->third = acoin->quarter = NULL;

	return acoin;
}

void process_coin(coin acoin) {
	if (acoin->val < 12) {
		acoin->dollars = acoin->val;
		return;
	} else if (acoin->val == 12) {
		acoin->dollars = 13;
		return;
	}
	
	acoin->half = create_coin(acoin->val / 2);
	acoin->third = create_coin(acoin->val / 3);
	acoin->quarter = create_coin(acoin->val / 4);

	process_coin(acoin->half);
	process_coin(acoin->third);
	process_coin(acoin->quarter);

	unsigned sub = acoin->half->dollars + acoin->third->dollars + acoin->quarter->dollars;

	if (sub > acoin->val) {
		acoin->dollars = sub;
	} else {
		acoin->dollars = acoin->val;
	}
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

	coin root_coin = create_coin(n);

	process_coin(root_coin);

	if (input != stdin) {
		fclose(input);
	}

	printf("%u\n", root_coin->dollars);
	
	return 0;
}
