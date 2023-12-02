#include "followLeft.h"
#include <stdbool.h>
#include <stdlib.h>

//for direction
#define MAP_VERTICAL_UP 1
#define MAP_VERTICAL_DOWN 2
#define MAP_HORIZONTAL_LEFT 3
#define MAP_HORIZONTAL_RIGHT 4

#define VERTICAL_DIRECTION -2
#define HORIZONTAL_DIRECTION -3

int left, forward, right, back;

struct monsterInfo{
	int monsterType;
	struct monsterInfo * next;
};

//for weapon and monster
int monsterBlood[5];				//bloods of monster 2, 3, 4	2 for fire, 3 for ice, 4 for electric
int multiplierPower[5][5];		//dim1 is weapon 2, 3, 4	2 for fire, 3 for ice, 4 for electric
					//dim2 is monster 2, 3, 4	2 for fire, 3 for ice, 4 for electric

struct monsterInfo * monsterList;				//record the monster in the path
struct monsterInfo * monsterListTmpPointer;		//tmp pointer
bool firstMeet = true;								//first meet

bool validRange(int N, int x, int y){
	bool valid = false;
	if(x >= 0 && x <= (N - 1) && y >= 0 && y <= (N - 1)){
		valid = true;
		return valid;
	}
	return valid;
}


void adjustDirection(int N, int maze[N][N], Cell start){
	if(forward == MAP_HORIZONTAL_LEFT){
		if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] >= 1){
			//adjust to left
			forward = MAP_VERTICAL_DOWN;
		}else if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] >= 1){
			//adjust to forward
			forward = MAP_HORIZONTAL_LEFT;
		}else if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] >= 1){
			//adjust to right
			forward = MAP_VERTICAL_UP;
		}
		else if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] >= 1){
			//adjust to back
			forward = MAP_HORIZONTAL_RIGHT;
		}
	}else if(forward == MAP_VERTICAL_UP){
		if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] >= 1){
			//adjust to left
			forward = MAP_HORIZONTAL_LEFT;
		}else if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] >= 1){
			//adjust to forward
			forward = MAP_VERTICAL_UP;
		}else if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] >= 1){
			//adjust to right
			forward = MAP_HORIZONTAL_RIGHT;
		}
		else if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] >= 1){
			//adjust to back
			forward = MAP_VERTICAL_DOWN;
		}
	}else if(forward == MAP_HORIZONTAL_RIGHT){
		if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] >= 1){
			//adjust to left
			forward = MAP_VERTICAL_UP;
		}else if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] >= 1){
			//adjust to forward
			forward = MAP_HORIZONTAL_RIGHT;
		}else if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] >= 1){
			//adjust to right
			forward = MAP_VERTICAL_DOWN;
		}
		else if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] >= 1){
			//adjust to back
			forward = MAP_HORIZONTAL_LEFT;
		}
	}else if(forward == MAP_VERTICAL_DOWN){
		if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] >= 1){
			//adjust to left
			forward = MAP_HORIZONTAL_RIGHT;
		}else if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] >= 1){
			//adjust to forward
			forward = MAP_VERTICAL_DOWN;
		}else if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] >= 1){
			//adjust to right
			forward = MAP_HORIZONTAL_LEFT;
		}
		else if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] >= 1){
			//adjust to back
			forward = MAP_VERTICAL_UP;
		}
	}

	/*
	if(inValidRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] == 1){
		//adjust to left
		left = MAP_VERTICAL_DOWN;
		forward = MAP_HORIZONTAL_LEFT;
		right = MAP_VERTICAL_UP;
		back = MAP_HORIZONTAL_RIGHT;
	}else if(inValidRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] == 1){
		//adjust to forward
		left = MAP_HORIZONTAL_LEFT;
		forward = MAP_VERTICAL_UP;
		right = MAP_HORIZONTAL_RIGHT;
		back = MAP_VERTICAL_DOWN;
	}else if(inValidRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] == 1){
		//adjusto right
		left = MAP_VERTICAL_UP;
		forward = MAP_HORIZONTAL_RIGHT;
		right = MAP_VERTICAL_DOWN;
		back = MAP_HORIZONTAL_LEFT;
	}else if(inValidRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] == 1){
		//adjust to back
		left = MAP_HORIZONTAL_RIGHT;
		forward = MAP_VERTICAL_DOWN;
		right = MAP_HORIZONTAL_LEFT;
		back = MAP_VERTICAL_UP;
	}
	*/
}

void initializeDirection(int N, int maze[N][N], Cell start){
	//initially only has a unique direction
	//maze[0 ~ N - 1][0 ~ N - 1]
	//adjustDirection(N, maze, start);
	if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] >= 1){
		//adjust to left
		left = MAP_VERTICAL_DOWN;
		forward = MAP_HORIZONTAL_LEFT;
		right = MAP_VERTICAL_UP;
		back = MAP_HORIZONTAL_RIGHT;
	}else if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] >= 1){
		//adjust to forward
		left = MAP_HORIZONTAL_LEFT;
		forward = MAP_VERTICAL_UP;
		right = MAP_HORIZONTAL_RIGHT;
		back = MAP_VERTICAL_DOWN;
	}else if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] >= 1){
		//adjusto right
		left = MAP_VERTICAL_UP;
		forward = MAP_HORIZONTAL_RIGHT;
		right = MAP_VERTICAL_DOWN;
		back = MAP_HORIZONTAL_LEFT;
	}else if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] >= 1){
		//adjust to back
		left = MAP_HORIZONTAL_RIGHT;
		forward = MAP_VERTICAL_DOWN;
		right = MAP_HORIZONTAL_LEFT;
		back = MAP_VERTICAL_UP;
	}
}


void goNextStep(int N, int maze[N][N], Cell * start){
	if(forward == MAP_HORIZONTAL_LEFT){
		start -> c = start -> c - 1;
	}else if(forward == MAP_VERTICAL_UP){
		start -> r = start -> r - 1;
	}else if(forward == MAP_HORIZONTAL_RIGHT){
		start -> c = start -> c + 1;
	}else if(forward == MAP_VERTICAL_DOWN){
		start -> r = start -> r + 1;
	}
	if(maze[start -> r][start -> c] >= 2){
		if(firstMeet){
			monsterListTmpPointer = monsterList = (struct monsterInfo *) malloc(sizeof(struct monsterInfo));
			monsterListTmpPointer -> monsterType = maze[start -> r][start -> c];
			monsterListTmpPointer -> next = 0x00;
			firstMeet = false;
		}else{
			monsterListTmpPointer -> next = (struct monsterInfo *) malloc(sizeof(struct monsterInfo));
			monsterListTmpPointer = monsterListTmpPointer -> next;
			monsterListTmpPointer -> monsterType = maze[start -> r][start -> c];
			monsterListTmpPointer -> next = 0x00;
		}
		maze[start -> r][start -> c] = 1;
	}
}

void countHitNums(int * hitNums, int M, Weapon weapon[M]){
	int currentMonsterType;
	int currentMonsterBlood;

	int currentWeaponIndex;
	int currentWeaponType;
	int currentWeaponAttackPower;
	int currentWeaponDurability;

	int currentRealAttackPower;
	int currentMultiplierPower;
	
	struct monsterInfo * traversePointer = monsterList;

	currentWeaponIndex = 0;
	currentWeaponType = weapon[currentWeaponIndex].type;
	currentWeaponAttackPower = weapon[currentWeaponIndex].atk;
	currentWeaponDurability = weapon[currentWeaponIndex].drb;

	while(traversePointer){
		currentMonsterType = traversePointer -> monsterType;
		currentMonsterBlood = monsterBlood[currentMonsterType];

		currentMultiplierPower = multiplierPower[currentWeaponType][currentMonsterType];
		currentRealAttackPower = currentMultiplierPower * currentWeaponAttackPower;

		while(currentMonsterBlood > 0){

			currentMonsterBlood = currentMonsterBlood - currentRealAttackPower;
			*hitNums = *hitNums + 1;
			--currentWeaponDurability;

			if(currentWeaponDurability <= 0){
				++currentWeaponIndex;
				currentWeaponType = weapon[currentWeaponIndex].type;
				currentWeaponAttackPower = weapon[currentWeaponIndex].atk;
				currentWeaponDurability = weapon[currentWeaponIndex].drb;

				currentMultiplierPower = multiplierPower[currentWeaponType][currentMonsterType];
				currentRealAttackPower = currentMultiplierPower * currentWeaponAttackPower;
			}
		}
		traversePointer = traversePointer -> next;
	}
}

int followLeft(int N, int maze[N][N], Cell start, Cell end, int M, Weapon weapon[M]){
	//define the bloods of monsters
	monsterBlood[2] = 100000;
	monsterBlood[3] = 100000;
	monsterBlood[4] = 200000;
	//
	
	//define the multiplierPower
	multiplierPower[2][2] = 1;
	multiplierPower[2][3] = 2;
	multiplierPower[2][4] = 1;

	multiplierPower[3][2] = 2;
	multiplierPower[3][3] = 1;
	multiplierPower[3][4] = 1;

	multiplierPower[4][2] = 1;
	multiplierPower[4][3] = 1;
	multiplierPower[4][4] = 2;
	//


	//initialize monster list


	//initialize hit numbers
	int hitNums;
	hitNums = 0;


	int counter = 0;
	initializeDirection(N, maze, start);
	while((start.r != end.r) || (start.c != end.c)){
		goNextStep(N, maze, &start);
		counter++;
		adjustDirection(N, maze, start);
	}

	countHitNums(&hitNums, M, weapon);

	return hitNums;
	//return counter;
}
