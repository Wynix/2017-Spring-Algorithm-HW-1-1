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

	int repeatcount;           // # of experiment for mergesort, quicksort
	int numberOfData;
	int rangeOfArray;		
	int *targetedArray;
	int n;
	//float algorithmcost[6][4];
	

	FILE* pFile;         // Pointer for file `input1.txt`
	pFile = fopen("input1.txt", "r");  // Open `input1.txt` via `pFile` with "r" mode
	fscanf(pFile, "%d", &repeatcount);       // read first line to know how many we have to iterate same experiment
	for (n = 0; n < repeatcount; n++) {
		fscanf(pFile, "%d", &numberOfData);//데이터갯수를 numberOfData에 저장

		targetedArray = malloc(sizeof(int)*numberOfData); //동적 할당 배열 생성


		//난수를 생성하고, 입력한다.
		srand(time(NULL));
		for (rangeOfArray = 0; rangeOfArray < numberOfData; rangeOfArray++) {
			targetedArray[rangeOfArray] = rand() % numberOfData + 1;
		} //numberOfData 크기의 행렬 targetedArray에 1부터 numberOfData까지의 자연수가 들어감.
		
		loopcount = 0;
		MergeSort(targetedArray, numberOfData);
		printf("%15d", loopcount);//시행횟수 저장
		//worst배열 생성 :정렬된 배열을 사용하자. : targetedArray 재활용
		loopcount = 0;
		MergeSort(targetedArray, numberOfData);
		//시행횟수 저장

		//numberOfData길이의 랜덤배열 생성
		for (rangeOfArray = 0; rangeOfArray < numberOfData; rangeOfArray++) {
			targetedArray[rangeOfArray] = rand() % numberOfData + 1;
		}
		loopcount = 0;
		QuickSort(targetedArray,0,numberOfData-1);
		//횟수 저장
		
		loopcount = 0;
		//wost 배열 생성할수도 있으나 기존거 재탕
		QuickSort(targetedArray, 0, numberOfData - 1);
		//횟수 저장

		free(targetedArray);//랜덤배열 동적할당 해제

		//각 횟수를 다른 곳에 저장

	
	}


	fclose(pFile); // Close access for `input1.txt` via file pointer `pFile`



	printf("%18s%18s%18s%18s%18s\n", "", "rand_Merge", "worst_Merge", "rand_Quick", "worst_Quick");
	puts("--------------------------------------------------------------------------------------------");
	
	return 0;
}