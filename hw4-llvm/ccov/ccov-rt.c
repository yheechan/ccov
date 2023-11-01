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
int coveredBranches = 0;

struct myStructType myArray[MAX] = {{0}};

// write final values
extern void _final_() {
	fp = fopen("./Coverage.dat", "w");

	int iter = 0;
	for (iter=0; iter<totalBranchCnt; iter++) {
		int doWhileFlag = 0;
		if (myArray[iter].trueCnt < 0) {
			myArray[iter].trueCnt = doWhileFlag;
		}

		if (myArray[iter].trueCnt > 0) {
			coveredBranches++;
		}
		if (myArray[iter].falseCnt > 0) {
			coveredBranches++;
		}

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

	float perc = (coveredBranches/(float)totalBranchCnt)*100.0;

	fprintf(fp, "Total: %d branches\nCovered: %d branches\nPercentage: %f\n", totalBranchCnt, coveredBranches, perc);
	printf("Total: %d branches\nCovered: %d branches\nPercentage: %f\n", totalBranchCnt, coveredBranches, perc);

	fclose(fp);
}

// initally written as 0 as adding probes
// read inital values and initate it
extern void _init_() {
	fp = fopen("./initCoverage.dat", "r") ;

	int iter = 0;
	char line[MAX];
	while (fgets(line, sizeof(line), fp)) {
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
	atexit(_final_);
}

// increment values
extern void _probe_(int idx, int lineNum, int idxNum, int tNum, int fNum) {
	myArray[idx].trueCnt += tNum;
	myArray[idx].falseCnt += fNum;
}
