#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

FILE * dbFile;
FILE * coverageFile;

struct myStructType {
	int idx;
	int lnNum;
	int condCnt;
	int trueCnt;
	int falseCnt;
	int branchCnt;
	int doType;
	int ticked;
};

int totalCondCnt = 0;
int totalBranchCnt = 0;
int coveredBranches = 0;

struct myStructType myArray[MAX] = {{0}};

// write final values
extern void _final_() {
	coverageFile = fopen("./Coverage.dat", "w");
	dbFile = fopen("./dbFile.dat", "w");

	coveredBranches = 0;

	int iter = 0;
	printf("before for\n");
	for (iter=0; iter<totalCondCnt; iter++) {

		// change -1 to 0 (only for dispay purpose in Coverage.dat)
		int doWhileFlag = 0;
		if (myArray[iter].trueCnt < 0) {
			doWhileFlag = 1;
		}

		// increment covered branch
		if (myArray[iter].trueCnt > 0) {
			coveredBranches++;
		}
		if (myArray[iter].falseCnt > 0) {
			coveredBranches++;
		}

		// if it was -1, change it to 0 for display purpose
		if (doWhileFlag == 1) {
			myArray[iter].trueCnt = 0;
		}

		// results
		printf("%d.%d -> %d, %d\n",
			myArray[iter].lnNum,
			myArray[iter].condCnt,
			myArray[iter].trueCnt,
			myArray[iter].falseCnt
		);

		fprintf(coverageFile, "%d.%d -> %d, %d\n",
			myArray[iter].lnNum,
			myArray[iter].condCnt,
			myArray[iter].trueCnt,
			myArray[iter].falseCnt
		);

		// if it was -1, change it back to -1
		if (doWhileFlag == 1) {
			myArray[iter].trueCnt = -1;
		}

		// update DB
		fprintf(dbFile, "%d,%d,%d,%d,%d,%d,%d\n",
			myArray[iter].idx,
			myArray[iter].lnNum,
			myArray[iter].condCnt,
			myArray[iter].trueCnt,
			myArray[iter].falseCnt,
			myArray[iter].branchCnt,
			myArray[iter].doType
		);
	}

	float perc = (coveredBranches/(float)totalBranchCnt)*100.0;

	printf("Total: %d branches\nCovered: %d branches\nPercentage: %f\n", totalBranchCnt, coveredBranches, perc);
	fprintf(coverageFile, "Total: %d branches\nCovered: %d branches\nPercentage: %f\n", totalBranchCnt, coveredBranches, perc);

	fclose(coverageFile);
	fclose(dbFile);
}

// initally written as 0 as adding probes
// read inital values and initate it
extern void _init_() {
	dbFile = fopen("./dbFile.dat", "r") ;

	int iter = 0;
	char line[MAX];
	while (fgets(line, sizeof(line), dbFile)) {
		sscanf(line, "%d,%d,%d,%d,%d,%d,%d\n",
			&myArray[iter].idx,
			&myArray[iter].lnNum,
			&myArray[iter].condCnt,
			&myArray[iter].trueCnt,
			&myArray[iter].falseCnt,
			&myArray[iter].branchCnt,
			&myArray[iter].doType
		);

		myArray[iter].ticked = 0;

		totalCondCnt++;
		totalBranchCnt = myArray[iter].branchCnt;
		iter++;
	}

	fclose(dbFile);
	atexit(_final_);
}

// increment values
extern void _probe_(int idx, int lineNum, int idxNum, int tNum, int fNum) {
	if (myArray[idx].doType == 1 && myArray[idx].ticked == 0) {
		if (fNum == 0) {
			myArray[idx].ticked = 1;
		} else {
			myArray[idx].falseCnt += fNum;
		}
	} else {
		myArray[idx].trueCnt += tNum;
		myArray[idx].falseCnt += fNum;
	}
}
