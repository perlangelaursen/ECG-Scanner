#include "peaks.h"
int rrHigh = 10000;

int detectPeak(int x[], int n, int size){
	//printf("%5d xn-1 %15d x: %5d xn+1:%5d\n", n, x[n-1], x[n], x[n+1]);
	if(x[(n-1+size)%size] < x[(n+size)%size] && x[(n+size)%size] > x[(n+1+size)%size]){
		 peaks[(i + peakSize) % peakSize] = x[(n-1+size)%size];
		 if(peaks[(i + peakSize) % peakSize] > thres1){
			 rr[(j + rrSize) % rrSize] = n - lastPeak;
			 rrOk[(j + rrSize) % rrSize] = n - lastPeakOk;

		//	 printf("RR__OK: %d\n", rrOk[(j + rrSize) % rrSize]);
			// printf("R_Peak: %d\n", peaks[(i + peakSize) % peakSize]);

			 //printf("j: %d\n", i);
			 //printf("n: %d\n", i);

			 if(rrLow <  rrOk[(j + rrSize) % rrSize] &&  rrOk[(j + rrSize) % rrSize] < rrHigh){
				 rPeaks[j] = peaks[(i + peakSize) % peakSize];
				 spkf = peaks[(i + peakSize) % peakSize]/8 + 7*spkf/8;

				 rrAverage1 = (rrAverage1*(rrSize-1) - rr[(j + 1 + rrSize) % rrSize] + rr[(j + rrSize) % rrSize])/8;
				 rrAverage2 = (rrAverage2*(rrSize-1) - rrOk[(j + 1 + rrSize) % rrSize] + rrOk[(j + rrSize) % rrSize])/8;

				 rrLow = 92*rrAverage2/100;
				 rrHigh = 116*rrAverage2/100;
				 rrMiss = 166*rrAverage2/100;

				 thres1 = npkf + (spkf-npkf)/4;
				 thres2 = thres1/2;

			 }else if(rrOk[(j + rrSize) % rrSize] > rrMiss){
				 int m = i;
				 while(peaks[(m + peakSize) % peakSize] <= thres2){
					 m--;
				 }
				 rPeaks[j] = peaks[(i + peakSize) % peakSize];
				 spkf = peaks[(i + peakSize) % peakSize]/8 + 7*spkf/8;

				 rrAverage1 = (rrAverage1*(rrSize-1) - rr[(j + 1 + rrSize) % rrSize] + rr[(j + rrSize) % rrSize])/8;

				 rrLow = 92*rrAverage2/100;
				 rrHigh = 116*rrAverage2/100;
				 rrMiss = 166*rrAverage2/100;

				 thres1 = npkf + (spkf-npkf)/4;
				 thres2 = thres1/2;
			 }

			 lastPeakOk = n;
			 j++;
		 }else{
			 npkf = peaks[(i + peakSize) % peakSize]/8 + 7*npkf/8;
			 thres1 = npkf + (spkf-npkf)/4;
			 thres2 = thres1/2;

		 }
		 lastPeak = n;
		 i++;
	}
	return 0;
}




