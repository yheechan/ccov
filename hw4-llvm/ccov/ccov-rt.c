#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

FILE * fp ;

struct myStructType {
	int idx;
	int lnNum;
	int condCnt;
	int trueCnt;
	int falseCnt;
};

int branchId = -1;
int totalBranchCnt = 0;

struct myStructType myArray[MAX] = {{0}};

// write final values
extern void _final_() {
	fp = fopen("Coverage.data", "w");

	int iter = 0;
	printf("Before for\n");
	for (iter=0; iter<totalBranchCnt; iter++) {
		printf("%d.%d -> %d, %d\n",
			myArray[iter].lnNum,
			myArray[iter].condCnt,
			myArray[iter].trueCnt,
			myArray[iter].falseCnt
		);

		fprintf(fp, "%d.%d -> %d, %d\n",
			myArray[iter].lnNum,
			myArray[iter].condCnt,
			myArray[iter].trueCnt,
			myArray[iter].falseCnt
		);
	}

	fclose(fp);
}

// initally written as 0 as adding probes
// read inital values and initate it
extern void _init_() {
	fp = fopen("initCoverage.dat", "r") ;

	int iter = 0;
	char line[MAX];
	printf("before while\n");
	while (fgets(line, sizeof(line), fp)) {
		printf("%d,%d,%d,%d,%d\n",
			myArray[iter].idx,
			myArray[iter].lnNum,
			myArray[iter].condCnt,
			myArray[iter].trueCnt,
			myArray[iter].falseCnt
		);

		sscanf(line, "%d,%d,%d,%d,%d\n",
			&myArray[iter].idx,
			&myArray[iter].lnNum,
			&myArray[iter].condCnt,
			&myArray[iter].trueCnt,
			&myArray[iter].falseCnt
		);

		branchId++;
		totalBranchCnt++;
		iter++;
	}

	fclose(fp);
	// atexit(_final_) ;
}

// increment values
extern void _probe_(int idx, int lineNum, int idxNum, int tNum, int fNum) {
	myArray[idx].trueCnt += tNum;
	myArray[idx].falseCnt += fNum;
}

extern void _hcy_(struct myStructType tmp[]) {
	fprintf(fp, "hcy here %d\n", 2);
}
