#include <stdio.h>
#include <math.h>
#include "sensor.h"


// Filter function declerations
int lowPass();
int highPass();
int derivative();
int squaring();
int movingWindowIntegration();

// arrays
int x[13], y[10011], lowpass[33], highpass[5], sq[30];
int n = 1, deri;

// Main program
int main(int argc, char *argv[]) {
	while(n < 15) {
		x[n % 13] = getNextData();
		//printf("%15d%15d%15d%15d%15d%15d%15d\n", n, x[n%13], lowPass(), highPass(), derivative(), squaring(), movingWindowIntegration());

		printf("%15d%15d%15d%15d\n", n, x[n%13], lowPass(), highPass());
		n++;
	}


	// End of program
	return 0;
}

// Filters here
int lowPass() {
	lowpass[n%33] = 2 * lowpass[(n-1)%33] - lowpass[(n-2)%33] + (x[n%13] - 2 * x[(n-6)%13] + x[(n-12)%13]) / 32;
	return lowpass[n%33];
}

int highPass() {
	highpass[n%5] = highpass[(n-1)%5] - lowpass[n%33] / 32.0 + lowpass[(n-16)%33] - lowpass[(n-17)%33] + lowpass[(n-32)%33] / 32.0;
	return highpass[n%5];
}

int derivative() {
	deri = 1.0 / 8.0 * (2 * highpass[n%5] + highpass[(n-1)%5] - highpass[(n-3)%5] - 2 * highpass[(n-4)%5]);
	return deri;
}

int squaring() {
	sq[n] *= deri;
	return sq[n];
}

int movingWindowIntegration() {

	int N = 30; // ????
	int buf = 0;

	for (int i = 1; i < N; i++) {
		buf += sq[(n-(N-i))%30];
	}

	y[n] = 1 / N * buf;
	return y[n];
}










