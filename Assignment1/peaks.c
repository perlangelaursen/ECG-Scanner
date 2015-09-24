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
static int rrRecent[rrSize] = {100,100,100,100,100,100,100,100};
static int rrRecentOk[rrSize] = {151,151,151,151,151,151,151,151};
static int sampleRate = 250;
static int peakCount = 0;
static int rpeakCount = 0;
static int missCount = 0;
static int timer = 0;
static int rrInterval = 0;

void detectPeak(int x[], int n, int size){
	if(x[calcPIndex(n, 1, size)] < x[n] && x[n] > x[calcPIndex(n, -1, size)]){
		 peaks[(peakCount+peakSize) % peakSize] = x[n];
		 if(peaks[(peakCount+peakSize) % peakSize] > thres1){

			 //printf("RR thresInterval: %d %5d %5d\n", rrInterval, peaks[(peakCount+peakSize) % peakSize],thres1);
			 if(rrLow <  rrInterval && rrInterval < rrHigh){

				 //printf("RR rrInterval: %d %5d %5d %5d\n", rrInterval, timer, peaks[(peakCount+peakSize) % peakSize]);

				 rpeak = peaks[(peakCount+peakSize) % peakSize];

				 bloodPressureCheck();

				 printf("Time: %5d R-Peak: %5d Pulse: %5d \n", timer, rpeak, (60*sampleRate)/rrInterval);
				 spkf = peaks[(peakCount+peakSize) % peakSize]/8 + 7*spkf/8;

				 rrRecentOk[(rpeakCount+rrSize) % rrSize] = rrInterval;
				 rrRecent[(rpeakCount+rrSize) % rrSize] = rrInterval;

				 rrAverage2 = calcRRAverage2();
				 rrAverage1 = calcRRAverage1();

				 rrLow = (lowVar*rrAverage2)/100;
				 rrHigh = (highVar*rrAverage2)/100;
				 rrMiss = (166*rrAverage2)/100;

				 thres1 = npkf + (spkf-npkf)/4;
				 thres2 = thres1/2;

				 rpeakCount++;
				 missCount = 0;

				 rrInterval = 0;
			 } else {
				//printf("MISS rrInterval: %d %5d %5d %5d\n", rr, timer, peaks[(peakCount+peakSize) % peakSize], rrInterval);
				missCount++;
				checkRRMiss();
				if(rrInterval > rrMiss) {
					int peak = searchBack();
					if(peak != 0){
						rpeak = peak;
						printf("Time: %5d R-Peak: %5d Pulse: %5d \n", timer, rpeak, (60*sampleRate)/rrInterval);
						spkf = peak/4 + (3*spkf)/4;

						rrRecent[(rpeakCount+rrSize) % rrSize] = rrInterval;

						rrAverage1 = calcRRAverage1();
						rrLow = (lowVar*rrAverage1)/100;
						rrHigh = (highVar*rrAverage1)/100;
						rrMiss = (166*rrAverage1)/100;

						thres1 = npkf + (spkf-npkf)/4;
						thres2 = thres1/2;
						rpeakCount++;

						 rrInterval = 0;
					}
				}
			 }
		 }else{
			 npkf = peaks[(peakCount+peakSize) % peakSize]/8 + (7*npkf)/8;
			 thres1 = npkf + (spkf-npkf)/4;
			 thres2 = thres1/2;

		 }
		 peakCount++;
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

	return sum/rrSize;
}

int calcRRAverage2(void) {

	int sum = 0;
	for(int i = 0; i < rrSize; i++) {
		sum += rrRecentOk[i];
	}

	return sum/rrSize;
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




