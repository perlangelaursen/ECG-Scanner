#include <stdio.h>
#include <math.h>

int divisionby30(int num);

int main() {
	int divisor = 180000;
	int div = 30;

	int result = divisor / div;
	int reuslt2 = divisionby30(divisor);
	if (result == reuslt2) {
		printf("\nJa");
	} else {
		printf("\nResult: %d\n", result);
		printf("Function: %d\n", reuslt2);
	}

}

int divisionby30(int num) {
	int Q = 0;
	int R = 0;

	// Finding the highest set bit
	int loops = 0;
	int buf = num;
	while (buf >>= 1) {
		loops++;
	}
	for(int i = loops; i >= 0; i--) {
		R = R << 1;

		if (num & (1 << i)) {
			R++;
		}

		if (R >= 30) {
			R -= 30;
			Q |= (1 << i);
		}
	}
	return Q;
}
