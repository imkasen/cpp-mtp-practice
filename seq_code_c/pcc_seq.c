#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lib/common.c"

int COLS = 128;
int ROWS = 128;

/**
 * Read tab delimited matrix file
 **/
int readmatrix(const char *filename, float *matrix){
	FILE *input;
	char *line = NULL;
	size_t size;
	char *token;
	int count = 0;

	input = fopen(filename, "r");
	if(input == NULL){
		return(-1);
	}

	while(getline(&line, &size, input) != -1){
		token = strtok(line, " ");
		matrix[count] = atof(token);
		count++;
		while( (token = strtok(NULL, " ")) != NULL){
			matrix[count] = atof(token);
			count++;
		}
	}

	fclose(input);
	free(line);
	return(0);
}

/**
 * Calculate row mean
 */
void calcmean(float *matrix, float *mean){
	int i,j;
	float sum;

	for(i = 0; i < ROWS; i++){
		sum = 0.0;
		for(j = 0; j < COLS; j++){
			sum += matrix[i * COLS + j];
		}
		mean[i] = sum / (float)COLS;
	}
}

/**
 * Calculate matrix - rowmean, and standard deviation for every row 
 */
void calc_mm_std(float *matrix, float *mean, float *mm, float *std){
	int i,j;
	float sum, diff;

	for(i = 0; i < ROWS; i++){
		sum = 0.0;
		for(j = 0; j < COLS; j++){
			diff = matrix[i * COLS + j] - mean[i];
			mm[i * COLS + j] = diff;
			sum += diff * diff;
		}
		std[i] = sqrtf(sum);
	}
}

void pearson(float *mm, float *std, float *output){
	int i, sample1, sample2;
	float sum,r;

	for(sample1 = 0; sample1 < ROWS-1; sample1++){
		int summ = 0;
		for(int l = 0; l <= sample1+1; l++)
			summ += l;

		for(sample2 = sample1+1; sample2 < ROWS; sample2++){
			sum = 0.0;
			for(i = 0; i < COLS; i++){
				sum += mm[sample1 * COLS + i] * mm[sample2 * COLS + i];
			}
			r = sum / (std[sample1] * std[sample2]);
			output[sample1 * ROWS + sample2 - summ] = r;
		}
	}
}

void pearson_seq(float *input, float *output, int cor_size){
    
    float *mean = (float*)malloc(sizeof(float) * ROWS);
	float *std  = (float*)malloc(sizeof(float) * COLS);
	
	if(mean == NULL || std == NULL){
        printf("did exit\n");
		exit(0);
	}
    float *minusmean = (float*)malloc(sizeof(float) * ROWS * COLS);
	if(minusmean == NULL) {
        printf("did exit\n");
		exit(0);
	}
    
    calcmean(input, mean);
	calc_mm_std(input, mean, minusmean, std);
	pearson(minusmean, std, output);

    free(mean);
    free(minusmean);
    free(std);
}

void writeoutput(float *output, int cor_size, char *name)
{
	FILE *f;

	f = fopen(name,"wb");
	for (int i = 0; i < cor_size; i++) {
		fprintf(f, "%f ", output[i]);
	}
	fclose(f);
}

int main(int argc, char **argv){
	
	if (argc < 4) { fprintf(stderr, "usage: %s matrix_file matrix_height matrix_width\n", argv[0]); exit(-1); }
	const char *filename = argv[1];

	ROWS = atoi(argv[2]);
	if (ROWS < 1) { fprintf(stderr, "error: height must be at least 1\n"); exit(-1); }

	COLS = atoi(argv[3]);
	if (COLS < 1) { fprintf(stderr, "error: width must be at least 1\n"); exit(-1); }


	//create an array of timers for each iteration
	double times[ITERATIONS];

	//used to generate the correct filename
	char output_filename[30];
	snprintf(output_filename, 30, "pccout_%d_%d.dat", ROWS, COLS);
	
	//calculates the size of the output
	long long cor_size = ROWS - 1;
    cor_size *= ROWS;
    cor_size /= 2;

	float *matrix, *minusmean, *mean, *std, *output;
	output = (float*)malloc(sizeof(float) * cor_size);
	matrix = (float*)malloc(sizeof(float) * COLS * ROWS);

	if(matrix == NULL){
		return(1);
	}
	
	readmatrix(filename, matrix);

	for(int i = 0; i < ITERATIONS; i ++) {
		times[i]= mysecond();
		pearson_seq(matrix, output, cor_size);
		times[i]= mysecond() - times[i];
	}
	
	print_results(times);

	writeoutput(output, cor_size, output_filename);	

	free(output);
	return(EXIT_SUCCESS);
}
