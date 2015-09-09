#include <stdio.h>
#include "sensor.h"

// Filter function declarations
int lowPass(int x[], int y[]);
int highPass(int x[], int y[]);
int derivative(int x[], int y[]);
int squaring(int y[]);
int movingWindowIntegration(int x[], int y[]);

// Main program
int main(int argc, char *argv[]) {
	int x[32], y[32];

	printf("%i\n", getNextData());
	printf("%i\n", getNextData());


	return 0;
}


// Filters here
int lowPass(int x[], int y[]) {
	int n = 32;
	y[n] = 2 * y[n-1] - y[n-2] + 1 / 32 * (x[n] - 2 * x[n-6] + x[n-12]);
	return y[n];
}

int highPass(int x[], int y[]) {
	int n = 32;
	y[n] = y[n-1] - x[n] / 32 + x[n-16] - x[n-17] + x[n-32] / 32;
	return y[n];
}

int derivative(int x[], int y[]) {
	int n = 32;
	y[n] = 1 / 8 * (2 * x[n] + x[n-1] - x[n-3] - 2 * x[n-4]);
	return y[n];
}

int squaring(int y[]) {
	int n = 32;
	y[n] = y[n] * y[n];
	return y[n];
}

int movingWindowIntegration(int x[], int y[]) {
	int n = 32;
	int N = 30; // ????
	int buf = 0;

	for (int i = 1; i < N; i++) {
		buf += x[n-(N-i)];
	}


	y[n] = 1 / N * buf;
	return y[n];
}










