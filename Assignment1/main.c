#include <stdio.h>
#include <math.h>
#include "sensor.h"

#define SIZE 33
#define N 30

// Filter function declarations
int lowPass(void);
int highPass(void);
int derivative(void);
int squaring(void);
int movingWindowIntegration(void);
int calculateIndex(int n, int i);
void checkIfNIsOutOfBounds();

int x[SIZE], y[SIZE], lowpassArray[SIZE], highpassArray[SIZE], derivativeArray[SIZE], squaredArray[SIZE];
int n = 0;

// Main program
int main(int argc, char *argv[]) {
	// Does not read the entire file
	while((x[n] = getNextData()) != EOF) {
		lowPass();
		highPass();
		derivative();
		squaring();
		movingWindowIntegration();

		printf("%15d:%15d\n",x[n], y[n]);
		n++;
		checkIfNIsOutOfBounds();
	}

	// End of program
	return 0;
}

// Filter Implementation
int lowPass(void) {
	lowpassArray[n] = (2*lowpassArray[calculateIndex(n, 1)]-
			lowpassArray[calculateIndex(n, 2)]+(x[n]-
			2*x[calculateIndex(n, 6)]+x[calculateIndex(n, 12)])/32);
	return lowpassArray[n];
}

int highPass(void) {
	highpassArray[n]=highpassArray[calculateIndex(n, 1)]-
			lowpassArray[n]/32+lowpassArray[calculateIndex(n, 16)]-
			lowpassArray[calculateIndex(n, 17)]+lowpassArray[calculateIndex(n, 32)]/32;
	return highpassArray[n];
}

int derivative() {
	derivativeArray[n]=(2*highpassArray[n]+highpassArray[calculateIndex(n, 1)]
						-highpassArray[calculateIndex(n, 3)]-
						2*highpassArray[calculateIndex(n, 4)])/8;
	return derivativeArray[n];
}

int squaring() {
	squaredArray[n] = derivativeArray[n]*derivativeArray[n];
	return squaredArray[n];
}

int movingWindowIntegration() {
	int buf = 0;

	for (int i = 1; i <= N; i++) {
		buf += squaredArray[calculateIndex(n, (N-i))];
	}

	y[n] = buf/N;
	return y[n];
}

void checkIfNIsOutOfBounds() {
	// Insures that the n variable never will be greater than the size of the array
	if (n >= SIZE) {
		n = 0;
	}
}

// Function calculates the previous index relative to the size of the array
int calculateIndex(int n, int i) {
	return (n-i+SIZE)%SIZE;
}










