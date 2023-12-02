#include <stdio.h>
#include <stdlib.h>
 
#include "countSum.h"
 
int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
int main() {
    int n, targetSum;
    scanf("%d", &n);
    scanf("%d", &targetSum);
    int set[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &set[i]);
    }
    qsort(set, n, sizeof(int), cmp);
 
    /*for(int i = 0; i < n; i++){
	    printf("%d\n", set[i]);
    }*/

    int uniqueSize = removeConsecutiveDuplicates(set, n);
 
    int result = countSubsetsWithSum(set, uniqueSize, targetSum, 0);
 
    printf("%d\n", result);
 
    return 0;
}
