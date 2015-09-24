#include <stdio.h>
#include <math.h>
#include <time.h>
#include "sensor.h"
#include "filter.h"
#include "peaks.h"

// Additional function
int readData();
int calcIndex(int n, int i, int size);

#define xSize 13
#define lowPassSize 33
#define highPassSize 5
#define squaredSize 31
#define ySize 3
int x[xSize], y[ySize];
int n = 0;

// Main program
int main(int argc, char *argv[]) {
	//printf("%15s%15s%15s\n", "Number", "Data Read", "Output");

	clock_t start, end;
	double cpu_time_used;
	start = clock();

	while(readData()) {
		dataFilter(x, xSize, y, ySize, n);

		//printf("%15d%15d%15d\n", n + 1, x[calcIndex(n, 0, xSize)], y[calcIndex(n, 0, ySize)]);

		detectPeak(y, calcIndex(n, 1, ySize), ySize);

		n++;
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("Time spent on entire program: %g\n", cpu_time_used);

	// End of program
	return 0;
}

int readData() {
	// Returns 1 if successful, 0 if EOF is read
	int dataRead = getNextData();

	if (dataRead == -1000) {
		return 0; // EOF
	}

	x[calcIndex(n, 0, xSize)] = dataRead;
	return 1;
}

// Function calculates the previous index relative to the size of the array
int calcIndex(int n, int i, int size) {
	return (n - i + size) % size;
}










