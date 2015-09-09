#include "sensor.h"

static const char filename[] = "Files/ECG.txt";
FILE *file;

int getNextData() {
	int returnVal;
	if (file == NULL) {
		file = fopen(filename, "r");
	}

	fscanf(file, "%i", &returnVal);
	return returnVal;
}
