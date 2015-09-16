#include <stdio.h>
#include <math.h>
#include "sensor.h"
#include "peaks.h"

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
int calcIndex(int n, int i, int size);
void checkIfNIsOutOfBounds();

#define xSize 13
#define lowPassSize 33
#define highPassSize 5
#define squaredSize 31
#define ySize 31
int x[xSize], y[ySize], lowpassArray[lowPassSize], highpassArray[highPassSize], derivativeNo, squaredArray[squaredSize];
int n = 0;

// Main program
int main(int argc, char *argv[]) {
	//printf("%15s%15s%15s\n", "Number", "Data Read", "Output");

	while(readData()) {
		lowPass();
		highPass();
		derivative();
		squaring();
		movingWindowIntegration();

		//printf("%15d%15d%15d\n", n + 1, x[calcIndex(n, 0, xSize)], y[calcIndex(n, 0, ySize)]);

		//checkIfNIsOutOfBounds();

		detectPeak(y, n - 1, ySize);

		n++;
	}

	printf("Stopped program\n");
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


// Filter Implementation
int lowPass() {
	lowpassArray[calcIndex(n, 0, lowPassSize)] = (2*lowpassArray[calcIndex(n, 1, lowPassSize)]-
			lowpassArray[calcIndex(n, 2, lowPassSize)]+(x[calcIndex(n, 0, xSize)]-
			2*x[calcIndex(n, 6, xSize)]+x[calcIndex(n, 12, xSize)])/32);
	return lowpassArray[calcIndex(n, 0, lowPassSize)];
}

int highPass() {
	highpassArray[calcIndex(n, 0, highPassSize)]=highpassArray[calcIndex(n, 1, highPassSize)]-
			lowpassArray[calcIndex(n, 0, lowPassSize)]/32+lowpassArray[calcIndex(n, 16, lowPassSize)]-
			lowpassArray[calcIndex(n, 17, lowPassSize)]+lowpassArray[calcIndex(n, 32, lowPassSize)]/32;
	return highpassArray[calcIndex(n, 0, highPassSize)];
}

int derivative() {
	derivativeNo = (2*highpassArray[calcIndex(n, 0, highPassSize)]+highpassArray[calcIndex(n, 1, highPassSize)]
						-highpassArray[calcIndex(n, 3, highPassSize)]-
						2*highpassArray[calcIndex(n, 4, highPassSize)])/8;
	return derivativeNo;
}

int squaring() {
	squaredArray[calcIndex(n, 0, squaredSize)] = derivativeNo*derivativeNo;
	return squaredArray[calcIndex(n, 0, squaredSize)];
}

int movingWindowIntegration() {
	int buf = 0;

	for (int i = 1; i <= N; i++) {
		buf += squaredArray[calcIndex(n, (N-i), squaredSize)];
	}

	y[calcIndex(n, 0, ySize)] = buf/N;
	return y[calcIndex(n, 0, ySize)];
}

void checkIfNIsOutOfBounds() {
	// Insures that the n variable never will be greater than the size of the array
	if (n >= SIZE) {
		n = 0;
	}
}

// Function calculates the previous index relative to the size of the array
int calcIndex(int n, int i, int size) {
	return (n - i + size) % size;
}










