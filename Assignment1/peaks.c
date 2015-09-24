#include "peaks.h"
static int rrHigh = 174; //Initial value Based on typical thresInterval of 150
static int rrMiss = 249; //Initial value Based on typical thresInterval of 150
static int rrLow = 138; // Initial value Based on typical thresInterval of 150
static int spkf = 4700; // Initial value Approx average of rpeaks
static int npkf = 2300; // Initial value
static int lowVar = 78;
static int highVar = 116;
static int thres1 = 3500;
static int thres2 = 1750;
static int peakCount = 0;
static int rpeakCount = 0;
static int missCount = 0;
static int recentCounter = 0;
static int recentOkCounter = 0;
static int timer = 0;
static int rrInterval = 0;

void detectPeak(int x[], int n, int size){
	if(x[calcPIndex(n, 1, size)] < x[n] && x[n] > x[calcPIndex(n, -1, size)]){
		 peaks[(peakCount+peakSize) % peakSize] = x[n];
		 if(peaks[(peakCount+peakSize) % peakSize] > thres1){

			 rr = calculateRR();
			 //printf("RR thresInterval: %d %5d %5d\n", rr, peaks[(peakCount+peakSize) % peakSize],thres1);
			 if(rrLow <  rr && rr < rrHigh){

				 //printf("RR rrInterval: %d %5d %5d %5d\n", rr, timer, peaks[(peakCount+peakSize) % peakSize]);
				 rrInterval = 0;

				 rpeak = peaks[(peakCount+peakSize) % peakSize];

				 bloodPressureCheck();

				 printf("%15d %15d %15R-Peak %15d %15d %15d\n", timer, rpeak, rrLow, rrHigh, thres1);
				 spkf = peaks[(peakCount+peakSize) % peakSize]/8 + 7*spkf/8;

				 rrRecentOk[(rpeakCount+rrSize) % rrSize] = rr;
				 rrRecent[(rpeakCount+rrSize) % rrSize] = rr;
				 recentCounter++;
				 recentOkCounter++;

				 rrAverage2 = calcRRAverage2();
				 rrAverage1 = calcRRAverage1();

				 rrLow = (lowVar*rrAverage2)/100;
				 rrHigh = (highVar*rrAverage2)/100;
				 rrMiss = (166*rrAverage2)/100;

				 thres1 = npkf + (spkf-npkf)/4;
				 thres2 = thres1/2;

				 rpeakCount++;
				 missCount = 0;

			 } else {
				//printf("MISS rrInterval: %d %5d %5d %5d\n", rr, timer, peaks[(peakCount+peakSize) % peakSize], rrInterval);
				missCount++;
				checkRRMiss();
				if(rr > rrMiss) {
					int peak = searchBack();
					if(peak != 0){
						rrInterval = 0;
						rpeak = peak;
						printf("%15d %15d %15Miss-Peak\n", timer, rpeak);
						spkf = peak/4 + (3*spkf)/4;

						rrRecent[(rpeakCount+rrSize) % rrSize] = rr;
						recentCounter++;

						rrAverage1 = calcRRAverage1();
						rrLow = (lowVar*rrAverage1)/100;
						rrHigh = (highVar*rrAverage1)/100;
						rrMiss = (166*rrAverage1)/100;

						thres1 = npkf + (spkf-npkf)/4;
						thres2 = thres1/2;
						rpeakCount++;

					}
				}
			 }
		 }else{
			 npkf = peaks[(peakCount+peakSize) % peakSize]/8 + (7*npkf)/8;
			 thres1 = npkf + (spkf-npkf)/4;
			 thres2 = thres1/2;

		 }
		 peakCount++;
		 //printf("\n Average1: %5d%5d \n ", rrAverage1, rrAverage2);
	}
	rrInterval++;
	timer++;
}

int searchBack(void) {
	for(int i = 0; i < peakSize; i++){
		if (peaks[(peakCount-i+peakSize)%peakSize] > thres2) {
			return peaks[(peakCount-i+peakSize)%peakSize];
		}
	}
	return 0;
}

void checkRRMiss(void) {
	if(missCount >= 5) {
		printf("HEART BEAT IRREGULAR SEEK MEDICAL ASSISTANCE%15d%15d\n", timer, rpeak);
		missCount = 0;
	}
}

int calcRRAverage1(void) {
	int sum = 0;
	for(int i = 0; i < rrSize; i++) {
		sum += rrRecent[i];
	}
	int no = (recentCounter <= rrSize) ? recentCounter : rrSize;

	return sum/no;
}

int calcRRAverage2(void) {

	int sum = 0;
	for(int i = 0; i < rrSize; i++) {
		sum += rrRecentOk[i];
	}
	int no = (recentOkCounter <= rrSize) ? recentOkCounter : rrSize;

	return sum/no;
}

int calculateRR(void) {
	int temp = rrInterval;
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




