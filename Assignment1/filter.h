/*
 * author: Per Lange Laursen (s144456)
 * memory optimized by Stefan Frederiksen (s144469)
 */

#include "index.h"

#define lowPassSize 33
#define highPassSize 5
#define squaredSize 31
#define N 30

static int lowpassArray[lowPassSize];
static int highpassArray[highPassSize];
static int derivativeNo;
static int squaredArray[squaredSize];

void dataFilter(int x[], int xSize, int y[], int ySize, int n);
void lowPass(int x[], int xSize, int n);
void highPass(int n);
void derivative(int n);
void squared(int n);
void movingWindowIntegration(int y[], int ySize, int n);
