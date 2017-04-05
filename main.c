//B411048 Kim Jeong Geol

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
int loopcount = 0;


int Partition(int *data, int left, int right, int pivot) {
	int pivotval = data[pivot];

	// swap value of pivot and right value
	int temp = data[pivot];
	data[pivot] = data[right];
	data[right] = temp;

	// scan from left to right
	int indexPoint;
	int s = left; // save left to stored index
	for (indexPoint = left; indexPoint < right; indexPoint++) {

		// if val is less than pivot value,
		if (data[indexPoint] < pivotval) {

			// swap val with stored index
			temp = data[s];
			data[s] = data[indexPoint];
			data[indexPoint] = temp;
			s++; // shift the stored index right
		}
		loopcount++;
	}

	/* swap the stored index with the right most
	* (bring the pivot back)
	*/
	temp = data[s];
	data[s] = data[right];
	data[right] = temp;
	return s;
}

void QuickSort(int *data, int left, int right) {
	if (left < right) {


		int pivot = left; //set pivot = the first data of array
		int newpivot = Partition(data, left, right, pivot);


		QuickSort(data, left, newpivot - 1); //do quicksort for left group
		QuickSort(data, newpivot + 1, right);//do quicksort for right group
	}
}

// Merge L and R to A 
// lefCount = number of elements in L
// rightCount = number of elements in R. 
void Merge(int *A, int *L, int leftCount, int *R, int rightCount) {


	int i = 0;  // i for index of left subarray (L)
	int j = 0;  // j for index of right subarray (R)
	int k = 0;  // k for index of merged subarray (A)

	while (i<leftCount && j< rightCount) {
		if (L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
		loopcount++;
	}
	while (i < leftCount) A[k++] = L[i++];
	while (j < rightCount) A[k++] = R[j++];
}

// Recursive function to sort an array of integers. 
void MergeSort(int *A, int n) {
	int mid, i, *L, *R;
	if (n < 2) return; //if size of array is 1, do nothing

	mid = n / 2;  // find mid and treat it as an index 



	L = (int*)malloc(mid * sizeof(int));  //define left subarray and allocate meomry space
	R = (int*)malloc((n - mid) * sizeof(int));  //define right subarray and allocate meomry space

	for (i = 0; i<mid; i++) L[i] = A[i]; // elements from [0] to [mid-1] will moves to L subarray
	for (i = mid; i<n; i++) R[i - mid] = A[i]; //elements from [mid] to [n-1] will moves to R subarray

	MergeSort(L, mid);  //tear L into smaller two subarray until size of subarry goes 1(because MergeSort is recursive function)
	MergeSort(R, n - mid);  //tear R into smaller two subarry until size of subarry goes 1(because MergeSort is recursive function)
	Merge(A, L, mid, R, n - mid);  // Merging L and R into A as sorted full-size array
	free(L);  //allocated memories goes free
	free(R);  //allocated memories goes free
}

int main() {

	int repeatcount;        // repeat time of every sort
	int numberOfData;		// scale of data
	int rangeOfArray;		// indicator for size of array
	int *targetedArray;		// sorted array
	int n;					// 'for' function indicator
	int avgMsortSum;		// loopcount for average Merge Sort
	int worstMsortSum;		// loopcount for worst Merge Sort
	int avgQsortSum;		// loopcount for average Quick Sort
	int worstQsortSum;		// loopcount for worst Quick Sort



	FILE* inputstream;         // make a pointer for 'input1.txt'
	inputstream = fopen("input1.txt", "r");  // open input1.txt with "r" mode through inputstream
	fscanf(inputstream, "%d", &repeatcount);  // read first line and save value at repeatcount

	printf("rand_Merge    worst_Merge    rand_Quick    worst_Quick");
	printf("---------------------------------------------------------------------------\n");

	while (!feof(inputstream)) {
		fscanf(inputstream, "%d", &numberOfData);
		loopcount = 0;
		avgMsort = 0;
		worstMsort = 0;
		avgQsort = 0;
		worstQsort = 0;

		targetedArray = malloc(sizeof(int)*numberOfData); //allocation array

		for (n = 0; n < repeatcount; n++){
			//make random number and input it
			srand(time(NULL));
			for (rangeOfArray = 0; rangeOfArray < numberOfData; rangeOfArray++) {
				targetedArray[rangeOfArray] = rand() % numberOfData + 1;
			} //targetedArray has size of numberOfData with random order

			MergeSort(targetedArray, numberOfData);  //for avearge case of Msort

			avgMsortSum += loopcount;
			loopcount = 0;


			MergeSort(targetedArray, numberOfData); //for worst case of Msort

			worstMsortSum += loopcount;
			loopcount = 0;

		}

		printf("%d", numberOfData);
		printf("%16d", avgMsortSum / 10);
		printf("%16d", worstMsortSum / 10);
		
		loopcount = 0;


		for (n = 0; n < repeatcount; n++){
			//remake array with random order
			for (rangeOfArray = 0; rangeOfArray < numberOfData; rangeOfArray++) {
				targetedArray[rangeOfArray] = rand() % numberOfData + 1;
			}
			QuickSort(targetedArray, 0, numberOfData - 1);  //for avarage case of Qsort

			avgQsortSum += loopcount;
			loopcount = 0;

			//use sorted array as worst case
			QuickSort(targetedArray, 0, numberOfData - 1);  //for worst case of Qsort

			worstQsortSum += loopcount;
			loopcount = 0;
		}
		printf("%16d", avgQsortSum / 10);
		printf("%16d\n", worstQsortSum / 10);
		
		loopcount = 0;
		free(targetedArray);//free allocted memories




	}


	fclose(inputstream); // close stream





	return 0;
}