#include <stdio.h>
#include <math.h>
#include "sensor.h"

// Not sure if useful...
//typedef enum { false = 0, true = !false } bool; /* Taken from stackoverflow
//				http://stackoverflow.com/questions/1921539/using-boolean-values-in-c
//				By Michael Potter */


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
int calculateIndex(int n, int i);
void checkIfNIsOutOfBounds();

int x[10001], y[10001], lowpassArray[10001], highpassArray[10001], derivativeArray[10001], squaredArray[10001];
int n = 0;

// Main program
int main(int argc, char *argv[]) {
	// Does not read the entire file

	printf("%15s%15s%15s\n", "Number", "Data Read", "Output");

	while(readData()) {
		lowPass();
		highPass();
		derivative();
		squaring();
		movingWindowIntegration();

		printf("%15d%15d%15d\n", n + 1, x[n], squaredArray[n]);
		n++;
		//checkIfNIsOutOfBounds();
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
	lowpassArray[n] = (2*lowpassArray[calculateIndex(n, 1)]-
			lowpassArray[calculateIndex(n, 2)]+(x[n]-
			2*x[calculateIndex(n, 6)]+x[calculateIndex(n, 12)])/32);
	return lowpassArray[n];
}

int highPass() {
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










