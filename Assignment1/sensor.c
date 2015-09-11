#include "sensor.h"

static const char filename[] = "Files/ECG.txt";
FILE *file;

int getNextData() {
	int returnVal; // The value which we return

	// Open the file if it isn't already opened
	if (file == NULL) {
		file = fopen(filename, "r");
	}

	// Read the number from the file
	fscanf(file, "%i", &returnVal);

	// Checks to see if the file has reached its end
	// and returns -1000 as our indicator that it ended
	if (feof(file)) {
		fclose(file);
		return -1000;
	}

	// Return this number
	return returnVal;
}
