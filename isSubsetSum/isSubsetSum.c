
#include <stdio.h>
#include <string.h>
#include "isSubsetSum.h"
#include <stdlib.h>
#include <stdbool.h>

bool check[157][600633];

int isSubsetSum(int set[], int n, int target_sum){
	int tmp;
	for(int i = 0; i <= n; i++){
		check[i][0] = true;
	}
	if(set[0] <= target_sum){
		check[1][set[0]] = true;
	}
	for(int i = 2; i <= n; i++){
		for(int j = 1; j <= target_sum; j++){
			tmp = j - set[i - 1];
			if(tmp >= 0){
				check[i][j] = check[i - 1][tmp];
			}
			check[i][j] = check[i][j] || check[i - 1][j];
		}
	}
	if(check[n][target_sum]){
		return 1;
	}else{
		return 0;
	}
}
			
/*
int start, end;
int isSubsetSum(int set[], int n, int target_sum){
	int test[n];
	int flag = 0;
	memset(test, 0, sizeof(test));
	test[0] = set[0];
	for(int i = 1; i <= n - 1; i++){
		test[i] = test[i - 1] + set[i];
	}
	
	if(test[0] == target_sum){
		flag = 1;
		return flag;
	}

	for(int i = 1; i <= n - 1; i++){
		if(test[i] == target_sum){
			flag = 1;
			//printf("start : %d, end : %d\n", 0, i);
			return flag;
		}
		for(int j = 0; j <= i - 1; j++){
			if((test[i] - test[j]) == target_sum){
				flag = 1;
				//printf("start : %d, end : %d\n", j + 1, i);
		       		return flag;
		 	}		
		}
	}
	return flag;
}
*/

/*
int addressTranslation(int x, int y, int target_sum){
	return x * (target_sum + 1) + y;
}

void setNum(bool * ary, int x, int y, bool value, int target_sum){
	*(ary + addressTranslation(x, y, target_sum)) = value;
}

bool getValue(bool * ary, int x, int y, int target_sum){
	return *(ary + addressTranslation(x, y, target_sum));
}

int isSubsetSum(int set[], int n, int target_sum){
	//subset sum using dynamic programming
	//row[0 ~ n] col[0 ~ target_sum]
	bool * twoDimArray = (bool *) malloc(sizeof(bool) * (n + 1) * (target_sum + 1));
	for(int i = 0; i < (n + 1) * (target_sum + 1); i++){
		*(twoDimArray + i) = false;
	}
	for(int i = 0; i <= target_sum; i++){
		setNum(twoDimArray, 0, i, false, target_sum);
	}
	if(set[0] <= target_sum){
		setNum(twoDimArray, 1, set[0], true, target_sum);
	}
	for(int i = 1; i <= n; i++){
		

		///
		if(i == 1){
			if(set[0] == 0){
				setNum(twoDimArray, i, 0, true, target_sum);
			}
			continue;
		}else{
			if(getValue(twoDimArray, i - 1, 0, target_sum) == true || set[i - 1] == 0){
				setNum(twoDimArray, i, 0, true, target_sum);
			}
		}
		


		setNum(twoDimArray, i, 0, true, target_sum);
	}

	for(int i = 2; i <= n; i++){
		for(int j = 1; j <= target_sum; j++){
			int tmp = set[i - 1];
			//case1
			if((j - tmp) >= 0 && (i - 1) >= 1){
				setNum(twoDimArray, i, j, getValue(twoDimArray, i - 1, j - tmp, target_sum), target_sum);
			}
			//case2
			if((i - 1) >= 1 && getValue(twoDimArray, i - 1, j, target_sum) == true){
				setNum(twoDimArray, i, j, true, target_sum);
			}
		}
	}

	if(getValue(twoDimArray, n, target_sum, target_sum))
		return 1;
	else
		return 0;
}
*/
//int sum = 0;
//int flag = false;
/*
int isSubsetSum(int set[], int n, int target_sum){
	if(n == 0 || target_sum < 0){
		//flag = false;
		return 0;
	}else if(target_sum == set[n - 1]){
		//flag = true;
		return 1;
	}else{
		return isSubsetSum(set, n - 1, target_sum - set[n - 1]) + isSubsetSum(set, n - 1, target_sum);
	}
}
*/	
