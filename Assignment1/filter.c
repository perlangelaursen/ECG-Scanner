#include "filter.h"

void dataFilter(int x[], int xSize, int y[], int ySize, int n) {
	lowPass(x, xSize, n);
	highPass(n);
	derivative(n);
	squaring(n);
	movingWindowIntegration(y, ySize, n);
}

void lowPass(int x[], int xSize, int n) {
	lowpassArray[calcFIndex(n, 0, lowPassSize)] = (2*lowpassArray[calcFIndex(n, 1, lowPassSize)]-
				lowpassArray[calcFIndex(n, 2, lowPassSize)]+(x[calcFIndex(n, 0, xSize)]-
				2*x[calcFIndex(n, 6, xSize)]+x[calcFIndex(n, 12, xSize)])/32);
}

void highPass(int n) {
	highpassArray[calcFIndex(n, 0, highPassSize)]=highpassArray[calcFIndex(n, 1, highPassSize)]-
				lowpassArray[calcFIndex(n, 0, lowPassSize)]/32+lowpassArray[calcFIndex(n, 16, lowPassSize)]-
				lowpassArray[calcFIndex(n, 17, lowPassSize)]+lowpassArray[calcFIndex(n, 32, lowPassSize)]/32;
}

void derivative(int n) {
	derivativeNo = (2*highpassArray[calcFIndex(n, 0, highPassSize)]+highpassArray[calcFIndex(n, 1, highPassSize)]
							-highpassArray[calcFIndex(n, 3, highPassSize)]-
							2*highpassArray[calcFIndex(n, 4, highPassSize)])/8;
}

void squaring(int n) {
	squaredArray[calcFIndex(n, 0, squaredSize)] = derivativeNo*derivativeNo;
}

void movingWindowIntegration(int y[], int ySize, int n) {
	int buf = 0;

	for (int i = 1; i <= N; i++) {
		buf += squaredArray[calcFIndex(n, (N-i), squaredSize)];
	}

	y[calcFIndex(n, 0, ySize)] = buf/N;
}

// Function calculates the previous index relative to the size of the array
int calcFIndex(int n, int i, int size) {
	return (n - i + size) % size;
}
