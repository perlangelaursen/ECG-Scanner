#include "peaks.h"
static int rrHigh = 246; //Initial value
static int rrMiss = 342; //Initial value
static int rrLow = 120; // Initial value
static int spkf = 4500; // Initial value
static int npkf = 2000; // Initial value
static int interval = 0;
static int peakCount = 0;
static int rpeakCount = 0;
static int missCount = 0;
static int time = 0;

void detectPeak(int x[], int n, int size){
	if(x[calcPIndex(n, 1, size)] < x[n] && x[n] > x[calcPIndex(n, -1, size)]){
		 peaks[(peakCount+peakSize) % peakSize] = x[n];
		 if(peaks[(peakCount+peakSize) % peakSize] > thres1) {

			 rr = calculateRR();

			 if(rrLow <  rr && rr < rrHigh) {
				 rpeak = peaks[(peakCount+peakSize) % peakSize];

				 bloodPressureCheck();

				 printf("%15d %15d\n", time, rpeak);
				 spkf = peaks[(peakCount+peakSize) % peakSize]/8 + 7*spkf/8;

				 rrRecentOk[(rpeakCount+rrSize) % rrSize] = rr;
				 rrRecent[(rpeakCount+rrSize) % rrSize] = rr;

				 rrAverage2 = calcRRAverage2();
				 rrAverage1 = calcRRAverage1();

				 rrLow = (92*rrAverage2)/100;
				 rrHigh = (116*rrAverage2)/100;
				 rrMiss = (166*rrAverage2)/100;

				 thres1 = npkf + (spkf-npkf)/4;
				 thres2 = thres1/2;

				 rpeakCount++;
				 missCount = 0;

			 } else {
				missCount++;
				checkRRMiss();
				if(rr > rrMiss) {
					int peak = searchBack();
					if(peak != NULL) {
						rpeak = peak;
						printf("%15d %15d\n", time, rpeak);
						spkf = peak/4 + (3*spkf)/4;

						rrRecent[(rpeakCount+rrSize) % rrSize] = rr;

						rrAverage1 = calcRRAverage1();
						rrLow = (92*rrAverage2)/100;
						rrHigh = (116*rrAverage2)/100;
						rrMiss = (166*rrAverage2)/100;

						thres1 = npkf + (spkf-npkf)/4;
						thres2 = thres1/2;
						rpeakCount++;
					}
				}
			 }
		 }
		 else {
			 npkf = peaks[(peakCount+peakSize) % peakSize]/8 + (7*npkf)/8;
			 thres1 = npkf + (spkf-npkf)/4;
			 thres2 = thres1/2;

		 }
		 peakCount++;
	}
	interval++;
}

int searchBack(void) {
	for(int i = 0; i < peakSize; i++){
		if (peaks[(peakCount-i+peakSize)%peakSize] > thres2) {
			return peaks[(peakCount-i+peakSize)%peakSize];
		}
	}
	return NULL;
}

void checkRRMiss(void) {
	if(missCount >= 5) {
		printf("HEART BEAT IRREGULAR\nSEEK MEDICAL ASSISTANCE\n");
		missCount = 0;
	}
}

int calcRRAverage1(void) {
	int sum = 0;
	for(int i = 0; i < rrSize; i++) {
		sum += rrRecent[i];
	}
	return sum/rrSize;
}

int calcRRAverage2(void) {
	int sum = 0;
	for(int i = 0; i < rrSize; i++) {
		sum += rrRecentOk[i];
	}
	return sum/rrSize;
}

int calculateRR(void) {
	int temp = interval;
	time += interval;
	interval = 0;
	return temp;
}

void bloodPressureCheck(void) {
	if (rpeak < 2000) {
		printf("BLOOD PRESSURE: %d\nSEEK MEDICAL ASSISTANCE\n", rpeak);
	}
}

// Function calculates the previous index relative to the size of the array
int calcPIndex(int n, int i, int size) {
	return (n - i + size) % size;
}




