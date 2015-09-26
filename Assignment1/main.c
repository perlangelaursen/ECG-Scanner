#include <stdio.h>
#include <math.h>
#include <time.h>
#include "sensor.h"
#include "filter.h"
#include "peaks.h"
#include "index.h"

// Additional function
int readData();
void startClock();
void pauseClock();
void unPauseClock();
void stopClock();

#define xSize 13
#define lowPassSize 33
#define highPassSize 5
#define squaredSize 31
#define ySize 3
int x[xSize], y[ySize];
int n = 0;

// For measuring code execution time
clock_t start, end;
double cpu_time_used;

// Main program
int main(int argc, char *argv[]) {
	//printf("%15s%15s%15s\n", "Number", "Data Read", "Output");

	startClock();


	while(readData()) {
		dataFilter(x, xSize, y, ySize, n);

		//printf("%15d%15d%15d\n", n + 1, x[calcIndex(n, 0, xSize)], y[calcIndex(n, 0, ySize)]);

		detectPeak(y, calcIndex(n, 1, ySize), ySize);

		n++;
	}

	stopClock();

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

void startClock() {
	start = clock();
}

void pauseClock() {
	end = clock();
}

void unPauseClock() {
	clock_t tempClock = clock();
	start += tempClock - end;
}

void stopClock() {
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
}
