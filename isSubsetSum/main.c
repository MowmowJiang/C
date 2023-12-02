#include <stdio.h>
#include <stdlib.h>
 
#include "isSubsetSum.h"
 
int main() {
    int n, target_sum;
    scanf("%d %d", &n, &target_sum);
 
    int set[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &set[i]);
    }
 
    if (isSubsetSum(set, n, target_sum)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
 
    return 0;
}