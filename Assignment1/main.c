#include <stdio.h>
#include <math.h>
#include "sensor.h"

#define SIZE 33
#define N 30

// Filter function declarations
int lowPass();
int highPass();
int derivative();
int squaring();
int movingWindowIntegration();

// Additional function
int readData();
int calcIndex(int n, int i);
void checkIfNIsOutOfBounds();

int x[SIZE], y[SIZE], lowpassArray[SIZE], highpassArray[SIZE], derivativeArray[SIZE], squaredArray[SIZE];
int n = 0;

// Main program
int main(int argc, char *argv[]) {
	printf("%15s%15s%15s\n", "Number", "Data Read", "Output");

	while(readData()) {
		lowPass();
		highPass();
		derivative();
		squaring();
		movingWindowIntegration();

		printf("%15d%15d%15d\n", n + 1, x[n], y[n]);
		n++;
		checkIfNIsOutOfBounds();
	}

	// End of program
	return 0;
}

int readData() {
	// Returns 1 if successful, 0 if EOF is read
	int dataRead = getNextData();

	if (dataRead == -1000) {
		return 0; // EOF
	}

	x[n] = dataRead;
	return 1;
}


// Filter Implementation
int lowPass() {
	lowpassArray[n] = (2*lowpassArray[calcIndex(n, 1)]-
			lowpassArray[calcIndex(n, 2)]+(x[n]-
			2*x[calcIndex(n, 6)]+x[calcIndex(n, 12)])/32);
	return lowpassArray[n];
}

int highPass() {
	highpassArray[n]=highpassArray[calcIndex(n, 1)]-
			lowpassArray[n]/32+lowpassArray[calcIndex(n, 16)]-
			lowpassArray[calcIndex(n, 17)]+lowpassArray[calcIndex(n, 32)]/32;
	return highpassArray[n];
}

int derivative() {
	derivativeArray[n]=(2*highpassArray[n]+highpassArray[calcIndex(n, 1)]
						-highpassArray[calcIndex(n, 3)]-
						2*highpassArray[calcIndex(n, 4)])/8;
	return derivativeArray[n];
}

int squaring() {
	squaredArray[n] = derivativeArray[n]*derivativeArray[n];
	return squaredArray[n];
}

int movingWindowIntegration() {
	int buf = 0;

	for (int i = 1; i <= N; i++) {
		buf += squaredArray[calcIndex(n, (N-i))];
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
int calcIndex(int n, int i) {
	return (n-i+SIZE)%SIZE;
}










