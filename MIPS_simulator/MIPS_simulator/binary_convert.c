#include "MIPS.h"

char Bin_temp[50];

int fromBinary(const char* s) {

	return (int)strtol(s, NULL, 2);
}

char* toBinary(int val) {
	char Bin_zero[50] = "";
	itoa(val, Bin_temp, 2);
	// TODO 32개에 맞게끔 앞에 0 추가
	while (strlen(Bin_temp) + strlen(Bin_zero) < 32) {
		strcat(Bin_zero, "0");
	}

	strcat(Bin_zero, Bin_temp);
	strcpy(Bin_temp, Bin_zero);
	//printf("\nzero is %s\n", Bin_zero);
	//printf("Bin_temp is %s\n", Bin_temp);
	//printf("op substr is %s\n", fromBinary(substr(Bin_temp, 0, 6)));
	// TODO fromBinary호출 잘 되나 확인


	return Bin_temp;
}