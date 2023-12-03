#include <stdio.h>
//#include <unistd.h>
//#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

//#define BUFFERSIZE 64

int buf[BUFFERSIZE];

struct employee {
	char name[32];
	int id;
	int age;
	int height;
	char favorite_food[32];
};

//char sel[15];


void insertionSort(struct employee * arr, int n){
	//sorted by struct employee array
	//array[0 ~ n - 1]
	int i, j;
	for(i = 1; i <= n - 1; i++){
		struct employee tmp = arr[i];
		for(j = i; j > 0; j--){
			if(tmp.id >= arr[j - 1].id){
				break;
			}
			arr[j] = arr[j - 1];
		}
		arr[j] = tmp;
	}
}


void Print(struct employee * arr, int n, int mode){
	if(mode == 1){
		for(int i = 0; i < n; i++){
			printf("%s: %d\n", arr[i].name, arr[i].age);
		}
	}else if(mode == 2){
		for(int i = 0; i < n; i++){
			printf("%s: %d\n", arr[i].name, arr[i].height);
		}
	}else if(mode == 3){
		for(int i = 0; i < n; i++){
			printf("%s: %s\n", arr[i].name, arr[i].favorite_food);
		}
	}
}
int main(int argc, int * argv[]){
	//3525
	int n;
	scanf("%d", &n);
	struct employee * arr = (struct employee *) malloc(sizeof(struct employee) * n);
	for(int i = 0; i < n; i++){
		scanf("%s", arr[i].name);
		scanf("%d%d%d", &arr[i].id, &arr[i].age, &arr[i].height);
		scanf("%s", arr[i].favorite_food);
	}

	scanf("%s", sel);
	insertionSort(arr, n);
	if(!strcmp(sel, "age")){
		Print(arr, n, 1);
	}else if(!strcmp(sel, "height")){
		Print(arr, n, 2);
	}else if(!strcmp(sel, "favorite_food")){
		Print(arr, n, 3);
	}	
	return 0;
}
