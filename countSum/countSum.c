#include <stdlib.h>
#include "countSum.h"

int check[100][2000] = {0};

int removeConsecutiveDuplicates(int set[], int n){
	//return unique size
	int count = 0;
	int pre = set[0];
	count++;
	for(int i = 1; i < n; i++){
		if(set[i] == pre){
			continue;
		}
		count++;
		pre = set[i];
	}
	int * foo = (int *) malloc(sizeof(int) * count);

	
	for(int i = 0, j = 0; i < n; i++, j++){
		pre = set[i];
		*(foo + j) = pre;
		while((i + 1) != n && pre == set[i + 1]){
			i++;
		}
	}

	for(int i = 0; i < n; i++){
		if(i < count){
			set[i] = *(foo + i);
		}else{
			set[i] = -1;
		}
	}
	return count;
}

int countSubsetsWithSum(int set[], int n, int targetSum, int idx){
	//using dynamic programming
	for(int i = 0; i <= n; i++){
		check[i][0] = 1;
	}
	if(set[0] <= targetSum){
		check[1][set[0]] = 1;
	}
	int tmp;
	for(int i = 2; i <= n; i++){
		for(int j = 1; j <= targetSum; j++){
			tmp = j - set[i - 1];
			if(tmp >= 0){
				check[i][j] = check[i - 1][tmp];
			}
			check[i][j] += check[i - 1][j];
		}
	}

	return check[n][targetSum];
}
