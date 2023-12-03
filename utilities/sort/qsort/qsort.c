#include "qsort.h"

void swap(int * arr, int x, int y){
	if(x == y) return;
	arr[x] ^= arr[y];
	arr[y] ^= arr[x];
	arr[x] ^= arr[y];
}

void qsort(int * arr, int start, int end){
	//arr[start ~ end]
	if(start >= end)
		return;
	else{
		int pivot;
		int leftPointer, rightPointer;
		pivot = arr[start];
		leftPointer = start;
		rightPointer = end + 1;

		while(leftPointer < rightPointer){
			do{++leftPointer;}while(arr[leftPointer] < pivot && leftPointer < end + 1);
			do{--rightPointer;}while(arr[rightPointer] >= pivot && rightPointer > start);
			if(leftPointer >= rightPointer) break;
			swap(arr, leftPointer, rightPointer);
		}
		swap(arr, rightPointer, start);
		qsort(arr, start, rightPointer - 1);
		qsort(arr, rightPointer + 1, end);
	}
}
