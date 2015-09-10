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
void checkIfNIsOutOfBounds();


// arrays
int x[SIZE], y[SIZE], lowpassArray[SIZE], highpassArray[SIZE], derivativeArray[SIZE], squaredArray[30];
int n = 0;

// Main program
int main(int argc, char *argv[]) {
	// Not sure if this will work
	while((x[n] = getNextData()) != EOF) {
		lowPass();
		highPass();
		derivative();
		squaring();
		movingWindowIntegration();

		printf("%15d:%15d", x[n], y[n]);

		n++;
		checkIfNIsOutOfBounds(n);
	}

	// End of program
	return 0;
}

// Filters here
int lowPass(void) {
	lowpassArray[n] = (2*lowpassArray[(n-1+SIZE)%SIZE]-lowpassArray[(n-2+SIZE)%SIZE]
						+(x[n]-2*x[(n-6+SIZE)%SIZE]+x[(n-12+SIZE)%SIZE])/32);
	return lowpassArray[n];
}

int highPass(void) {
	// Uses floats
	highpassArray[n]=highpassArray[(n-1+SIZE)%SIZE]-lowpassArray[n]/32.0+
			lowpassArray[(n-16+SIZE)%SIZE]-lowpassArray[(n-17+SIZE)%SIZE]+
			lowpassArray[(n-32+SIZE)%SIZE]/32.0;
	return highpassArray[n];
}

int derivative() {
	derivativeArray[n]= (2*highpassArray[n]+highpassArray[(n-1+SIZE)%SIZE]-
			highpassArray[(n-3+SIZE)%SIZE]-2*highpassArray[(n-4+SIZE)%SIZE])/8;
	return derivativeArray[n];
}

int squaring() {
	squaredArray[n] = derivativeArray[n]*derivativeArray[n];
	return squaredArray[n];
}

int movingWindowIntegration() {
	int buf = 0;

	for (int i = 1; i < N; i++) {
		buf += squaredArray[(n-(N-i)+SIZE)%SIZE];
	}

	y[n] = buf/N;
	return y[n];
}

void checkIfNIsOutOfBounds() {
	if (n >= SIZE) {
		n = 0;
	}
}










