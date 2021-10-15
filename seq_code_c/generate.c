#include <stdio.h>
#include <stdlib.h>

/**
 * This program generates a very big matrix to test my new correlation
 * calculator
*/

int main(int argc, char **argv){
	if (argc < 3) { fprintf(stderr, "usage: %s matrix_height matrix_width\n", argv[0]); exit(-1); }

	int height = atoi(argv[1]);
	if (height < 1) { fprintf(stderr, "error: height must be at least 1\n"); exit(-1); }
	int width = atoi(argv[2]);
	if (width < 1) { fprintf(stderr, "error: width must be at least 1\n"); exit(-1); }
	int i,j;

	for(i = 0; i < height; i++){
		for(j = 0; j < width-1; j++){
			printf("%.3f ",drand48());
		}
		printf("%.3f\n", drand48());
	}
}
