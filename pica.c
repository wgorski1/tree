//https://www.spoj.com/problems/PICAD/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	unsigned int start, end;
	unsigned int duration;
	unsigned short people;

	FILE *input = fopen("data.txt", "r");

	fscanf(input, "%u %u", &start, &end);
	duration = end - start + 1;

	unsigned short *timepoints = calloc(sizeof(unsigned short), duration);

        fscanf(input, "%hu", &people);
	int cnt;
	unsigned int entered;
	unsigned int left;
	//unsigned int visit;
	//unsigned int duration_start;

	for (cnt = 0; cnt < people; cnt++) {
		fscanf(input, "%u %u", &entered, &left);

		if (left < start || entered > end) {
			continue;
		}
		
		//visit = left - entered + 1;

		unsigned short *needle = timepoints + ((entered < start) ? 0 : entered - start);
		unsigned short *last = ((left >= end) ? timepoints + duration - 1 : needle + (left - (start > entered ? entered : start)));

		do {
			(*needle)++;
		} while (needle++ != last);
	}

	fclose(input);
	
	unsigned short min = people;
	unsigned short max = 0;

	unsigned short *ptr = timepoints;
	
	do {
		min = *ptr < min ? *ptr : min;
		max = *ptr > max ? *ptr : max;
	} while (ptr++ < timepoints + duration - 1);
	

	free(timepoints);

	printf("%hu %hu\n", min, max);
}
