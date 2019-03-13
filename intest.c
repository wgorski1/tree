// https://www.codechef.com/problems/INTEST


#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
	FILE *input;
	unsigned int n, k;

	if (argc > 1) {
		input = fopen(*(argv + 1), "r");
	} else {
		input = stdin;
	}

	fscanf(input, "%u %u", &n, &k);

	//const int buffer_size = 3000000;   // over 2.5 MB
	const int buffer_size = 10;

	char *buffer = malloc(buffer_size);

	size_t read, from_prev = 0, overread = 0;
	unsigned result = 0;

	while ((read = fread(buffer + from_prev, 1, buffer_size - from_prev, input)) > 0) {
		overread = 0;
		char *last_newline = buffer + from_prev + read - 1;

		if (!feof(input)) {
			while (*last_newline != '\n') {
				last_newline--;
				overread++;
			}
		}

		FILE *buf_stream = fmemopen(buffer, from_prev + read - overread, "r");
		int value;

		while (fscanf(buf_stream, "%i", &value) > 0) {
			if (value % k == 0) {
				result++;
			}
		}

		int x;
		for (x = 0; x < overread; x++) {
			buffer[x] = *++last_newline;
		}
		
		from_prev = overread;

		fclose(buf_stream);
	}

	if (input != stdin) {
		fclose(input);
	}

	free(buffer);

	printf("%u\n", result);
	
	return 0;
}
