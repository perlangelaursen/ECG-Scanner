/*
 * author: Per Lange Laursen (s144456)
 */

#include "index.h"

int calcIndex(int n, int i, int size) {
	return (n - i + size) % size;
}
