#include "peaks.h"
static int rrHigh = 10000;
static int interval = 0;
static int peakCount = 0;
static int rpeakCount = 0;
static int missCount = 0;
static int time = 0;

int detectPeak(int x[], int n, int size){
	int isPeakDetected = 0;

	if(x[calcPIndex(n, 1, size)] < x[n] && x[n] > x[calcPIndex(n, -1, size)]){
		 peaks[(peakCount) % peakSize] = x[n];
		 if(peaks[(peakCount) % peakSize] > thres1)
		 {

			 rr = calculateRR();

			 if(rrLow <  rr && rr < rrHigh)
			 {
				 rpeak = peaks[(peakCount) % peakSize];

				 printf("%15d %15d\n", time, rpeak);
				 spkf = peaks[(peakCount) % peakSize]/8 + 7*spkf/8;

				 rrRecentOk[(rpeakCount) % rrSize] = rr;
				 rrRecent[(rpeakCount) % rrSize] = rr;

				 rrAverage2 = calcRRAverage2();
				 rrAverage1 = calcRRAverage1();

				 rrLow = 92*rrAverage2/100;
				 rrHigh = 116*rrAverage2/100;
				 rrMiss = 166*rrAverage2/100;

				 thres1 = npkf + (spkf-npkf)/4;
				 thres2 = thres1/2;

				 rpeakCount++;
				 missCount = 0;

				 isPeakDetected = 1;

			 } else
			 {
				 missCount++;

				 if(rr > rrMiss)
				 {
					 int peak = searchBack();
					 if(peak != NULL)
					 {
						 rpeak = peak;
						 printf("%15d %15d\n", time, rpeak);
						 spkf = peak/8 + 7*spkf/8;

						 rrRecent[(rpeakCount) % rrSize] = rr;

						 rrAverage1 = calcRRAverage1();
						 rrLow = 92*rrAverage1/100;
						 rrHigh = 116*rrAverage1/100;
						 rrMiss = 166*rrAverage1/100;

						 thres1 = npkf + (spkf-npkf)/4;
						 thres2 = thres1/2;
						 rpeakCount++;
					 }
				 }
			 }
		 }
		 else
		 {
			 npkf = peaks[(peakCount) % peakSize] + 7*npkf/8;
			 thres1 = npkf + (spkf-npkf)/4;
			 thres2 = thres1/2;

		 }
		 peakCount++;
	}
	interval++;

	return isPeakDetected;
}

int searchBack(void) {
	int i = 0;
	while(i < peakSize) {
		if (peaks[(peakCount-i)%peakSize] > thres2) {
			return peaks[(peakCount-i)%peakSize];
		}
		i++;
	}
	return NULL;
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

// Function calculates the previous index relative to the size of the array
int calcPIndex(int n, int i, int size) {
	return (n - i + size) % size;
}




