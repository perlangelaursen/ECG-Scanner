#include <stdio.h>
#include <stdlib.h>

#define peakSize 800
#define rrSize 9
int peaks[peakSize], rPeaks[1000], rr[rrSize], rrOk[rrSize];
int i, j, lastPeak, lastPeakOk, thres1, thres2, spkf, npkf, rrAverage1, rrAverage2, rrLow, rrMiss;
int rrHigh;

int detectPeak(int x[], int n, int size);
