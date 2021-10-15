#include <sys/time.h>

# ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
# endif
# ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
# endif

int ITERATIONS = 10;

double mysecond() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

void print_results(double *times){
    static double	avgtime = 0, maxtime = 0, mintime = 3.402823466E+38;
    printf("#\tTime (s)");
    for (int k = 0; k<ITERATIONS; k++) 
	{
		avgtime += times[k];
		mintime = MIN(mintime, times[k]);
		maxtime = MAX(maxtime, times[k]);
        printf("\n%d\t%.4f", k, times[k]);
	}

	if(ITERATIONS > 1)
		avgtime = avgtime/(double)(ITERATIONS);
    
    printf("\n\nAvg. time: %.4f (s)\nMin. time: %.4f (s)\nMax. time: %.4f (s)\n", avgtime, mintime, maxtime);
}