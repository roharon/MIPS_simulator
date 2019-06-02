#include "MIPS.h"

char *substr(char *pnInput, int nStart, int nLen) {
	// 문자열, 시작지점, 길이
	int nLoop;
	int nLength;
	char *pszOutPut;

	if (pnInput == NULL) {
		return NULL;
	}
	pszOutPut = (char *)malloc(sizeof(char) * nLen + 1);
	nLength = strlen(pnInput);

	if (nLength > nStart + nLen) {
		nLength = nStart + nLen;
	}
	for (nLoop = nStart; nLoop < nLength; nLoop++) {
		pszOutPut[nLoop - nStart] = pnInput[nLoop];
	}

	pszOutPut[nLoop - nStart] = '\0';
	return pszOutPut;

}