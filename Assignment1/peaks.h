#include <stdio.h>
#include <stdlib.h>

#define peakSize 800
#define rrSize 8
static int peaks[peakSize], rPeaks[1000], rrRecent[rrSize], rrRecentOk[rrSize];
static int i, j, lastPeak, lastPeakOk, thres1, thres2, spkf, npkf, rr, rrAverage1, rrAverage2, rrLow, rrMiss;
static int interval, peakCount, rpeakCount, missCount;
static int rrHigh, rpeak;

int detectPeak(int x[], int n, int size);
int calculateRR(void);
int calcRRAverage1(void);
int calcRRAverage2(void);
int searchBack(void);
int calcPIndex(int n, int i, int size);
