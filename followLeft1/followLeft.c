#include "followLeft.h"
#include <stdbool.h>

#define MAP_VERTICAL_UP 1
#define MAP_VERTICAL_DOWN 2
#define MAP_HORIZONTAL_LEFT 3
#define MAP_HORIZONTAL_RIGHT 4

#define VERTICAL_DIRECTION -2
#define HORIZONTAL_DIRECTION -3

//int direction;
int left, forward, right, back;


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
		if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] == 1){
			//adjust to left
			forward = MAP_VERTICAL_DOWN;
		}else if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] == 1){
			//adjust to forward
			forward = MAP_HORIZONTAL_LEFT;
		}else if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] == 1){
			//adjust to right
			forward = MAP_VERTICAL_UP;
		}
		else if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] == 1){
			//adjust to back
			forward = MAP_HORIZONTAL_RIGHT;
		}
	}else if(forward == MAP_VERTICAL_UP){
		if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] == 1){
			//adjust to left
			forward = MAP_HORIZONTAL_LEFT;
		}else if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] == 1){
			//adjust to forward
			forward = MAP_VERTICAL_UP;
		}else if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] == 1){
			//adjust to right
			forward = MAP_HORIZONTAL_RIGHT;
		}
		else if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] == 1){
			//adjust to back
			forward = MAP_VERTICAL_DOWN;
		}
	}else if(forward == MAP_HORIZONTAL_RIGHT){
		if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] == 1){
			//adjust to left
			forward = MAP_VERTICAL_UP;
		}else if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] == 1){
			//adjust to forward
			forward = MAP_HORIZONTAL_RIGHT;
		}else if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] == 1){
			//adjust to right
			forward = MAP_VERTICAL_DOWN;
		}
		else if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] == 1){
			//adjust to back
			forward = MAP_HORIZONTAL_LEFT;
		}
	}else if(forward == MAP_VERTICAL_DOWN){
		if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] == 1){
			//adjust to left
			forward = MAP_HORIZONTAL_RIGHT;
		}else if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] == 1){
			//adjust to forward
			forward = MAP_VERTICAL_DOWN;
		}else if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] == 1){
			//adjust to right
			forward = MAP_HORIZONTAL_LEFT;
		}
		else if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] == 1){
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
	if(validRange(N, start.r, start.c - 1) && maze[start.r][start.c - 1] == 1){
		//adjust to left
		left = MAP_VERTICAL_DOWN;
		forward = MAP_HORIZONTAL_LEFT;
		right = MAP_VERTICAL_UP;
		back = MAP_HORIZONTAL_RIGHT;
	}else if(validRange(N, start.r - 1, start.c) && maze[start.r - 1][start.c] == 1){
		//adjust to forward
		left = MAP_HORIZONTAL_LEFT;
		forward = MAP_VERTICAL_UP;
		right = MAP_HORIZONTAL_RIGHT;
		back = MAP_VERTICAL_DOWN;
	}else if(validRange(N, start.r, start.c + 1) && maze[start.r][start.c + 1] == 1){
		//adjusto right
		left = MAP_VERTICAL_UP;
		forward = MAP_HORIZONTAL_RIGHT;
		right = MAP_VERTICAL_DOWN;
		back = MAP_HORIZONTAL_LEFT;
	}else if(validRange(N, start.r + 1, start.c) && maze[start.r + 1][start.c] == 1){
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
}


int followLeft(int N, int maze[N][N], Cell start, Cell end){
	int counter = 0;
	initializeDirection(N, maze, start);
	while((start.r != end.r) || (start.c != end.c)){
		goNextStep(N, maze, &start);
		counter++;
		adjustDirection(N, maze, start);
	}
	return counter;
}
