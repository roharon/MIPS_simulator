#include "MIPS.h"

char Bin_temp[50];

int fromBinary(const char* s) {
	return (int)strtol(s, NULL, 2);
}

char* toBinary(int val) {
	char result[50];
	itoa(val, Bin_temp, 2);

	return Bin_temp;
}