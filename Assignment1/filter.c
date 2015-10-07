/*
 * author: Per Lange Laursen (s144456)
 * memory optimized by Stefan Frederiksen (s144469)
 */

#include "filter.h"

void dataFilter(int x[], int xSize, int y[], int ySize, int n) {
	lowPass(x, xSize, n);
	highPass(n);
	derivative(n);
	squared(n);
	movingWindowIntegration(y, ySize, n);
}

void lowPass(int x[], int xSize, int n) {
	lowpassArray[calcIndex(n, 0, lowPassSize)] = (2*lowpassArray[calcIndex(n, 1, lowPassSize)]-
				lowpassArray[calcIndex(n, 2, lowPassSize)]+(x[calcIndex(n, 0, xSize)]-
				2*x[calcIndex(n, 6, xSize)]+x[calcIndex(n, 12, xSize)])/32);
}

void highPass(int n) {
	highpassArray[calcIndex(n, 0, highPassSize)]=highpassArray[calcIndex(n, 1, highPassSize)]-
				lowpassArray[calcIndex(n, 0, lowPassSize)]/32+lowpassArray[calcIndex(n, 16, lowPassSize)]-
				lowpassArray[calcIndex(n, 17, lowPassSize)]+lowpassArray[calcIndex(n, 32, lowPassSize)]/32;
}

void derivative(int n) {
	derivativeNo = (2*highpassArray[calcIndex(n, 0, highPassSize)]+highpassArray[calcIndex(n, 1, highPassSize)]
							-highpassArray[calcIndex(n, 3, highPassSize)]-
							2*highpassArray[calcIndex(n, 4, highPassSize)])/8;
}

void squared(int n) {
	squaredArray[calcIndex(n, 0, squaredSize)] = derivativeNo*derivativeNo;
}

void movingWindowIntegration(int y[], int ySize, int n) {
	buf *= N;
	buf -= squaredArray[calcIndex(n, 30, squaredSize)];
	buf += squaredArray[calcIndex(n, 0, squaredSize)];
	buf /= N;

	y[calcIndex(n, 0, ySize)] = buf;
}
