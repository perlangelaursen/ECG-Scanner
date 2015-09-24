#include <stdio.h>
#include <stdlib.h>

#define peakSize 800
#define rrSize 8
static int peaks[peakSize], rrRecent[rrSize], rrRecentOk[rrSize];
static int thres1, thres2, spkf, npkf, rr, rrAverage1, rrAverage2, rrLow, rrMiss;
static int rrInterval, peakCount, rpeakCount, missCount;
static int rrHigh, rpeak, timer;

void detectPeak(int x[], int n, int size);
int calculateRR(void);
int calcRRAverage1(void);
int calcRRAverage2(void);
int searchBack(void);
void checkRRMiss(void);
void bloodPressureCheck(void);
int calcPIndex(int n, int i, int size);
