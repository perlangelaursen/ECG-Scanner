#include "peaks.h"
static int rrHigh = 174; //Initial value Based on typical thresInterval of 150
static int rrMiss = 249; //Initial value Based on typical thresInterval of 150
static int rrLow = 138; // Initial value Based on typical thresInterval of 150
static int spkf = 4700; // Initial value Approx average of rpeaks
static int npkf = 2300; // Initial value Approx average of noise peak
const int lowVar = 78;
const int highVar = 116;
const int missVar = 166;
const int sampleRate = 250;
static int thres1 = 3500;
static int thres2 = 1750;
static int rrRecent[rrSize] = {100,100,100,100,100,100,100,100};
static int rrRecentOk[rrSize] = {151,151,151,151,151,151,151,151};
static int peakCount = 0;
static int rPeakCount = 0;
static int rrMissCount = 0;
static int timer = 0;
static int rrInterval = 0;

void detectPeak(int x[], int n, int size){
	if(x[calcIndex(n, 1, size)] < x[n] && x[n] > x[calcIndex(n, -1, size)]){
		 peaks[(peakCount+peakSize) % peakSize] = x[n];
		 if(peaks[(peakCount+peakSize) % peakSize] > thres1){
			 if(rrLow <  rrInterval && rrInterval < rrHigh){

				 rpeak = peaks[(peakCount+peakSize) % peakSize];

				 rPeakCheck();

				 printf("Time: %5d R-Peak: %5d Pulse: %5d \n", timer, rpeak, (60*sampleRate)/rrInterval);
				 spkf = peaks[(peakCount+peakSize) % peakSize]/8 + 7*spkf/8;

				 rrRecentOk[(rPeakCount+rrSize) % rrSize] = rrInterval;
				 rrRecent[(rPeakCount+rrSize) % rrSize] = rrInterval;

				 rrAverage2 = calcRRAverage2();
				 rrAverage1 = calcRRAverage1();

				 calcRRValues(rrAverage2);

				 calcThreshold();

				 rPeakCount++;
				 rrMissCount = 0;

				 rrInterval = 0;
			 } else {
				rrMissCount++;
				checkRRMiss();
				if(rrInterval > rrMiss) {
					int peak = searchBack();
					if(peak != 0){
						rpeak = peak;
						printf("Time: %5d R-Peak: %5d Pulse: %5d \n", timer, rpeak, (60*sampleRate)/rrInterval);
						spkf = peak/4 + (3*spkf)/4;

						rrRecent[(rPeakCount+rrSize) % rrSize] = rrInterval;

						rrAverage1 = calcRRAverage1();
						calcRRValues(rrAverage1);

						calcThreshold();
						rPeakCount++;

						rrInterval = 0;
					}
				}
			 }
		 }else{
			 npkf = peaks[(peakCount+peakSize) % peakSize]/8 + (7*npkf)/8;
			 calcThreshold();
		 }
		 peakCount++;
	}
	rrInterval++;
	timer++;
}

void calcThreshold(void) {
	thres1 = npkf + (spkf-npkf)/4;
	thres2 = thres1/2;
}

void calcRRValues(int avg) {
	rrLow = (lowVar*avg)/100;
	rrHigh = (highVar*avg)/100;
	rrMiss = (missVar*avg)/100;
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
	if(rrMissCount >= 5) {
		printf("HEART BEAT IRREGULAR SEEK MEDICAL ASSISTANCE%15d%15d\n", timer, rpeak);
		rrMissCount = 0;
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


void rPeakCheck(void) {
	if (rpeak < 2000) {
		printf("BLOOD PRESSURE: %d\nSEEK MEDICAL ASSISTANCE\n", rpeak);
	}
}




