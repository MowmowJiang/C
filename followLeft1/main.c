#include <stdio.h>
 
#include "followLeft.h"
 
int main(void)
{
    int N;
    scanf("%d", &N);
 
    int maze[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
 
    Cell start, end;
    scanf("%d%d%d%d", &start.r, &start.c, &end.r, &end.c);
 
    int step = followLeft(N, maze, start, end);
    printf("%d\n", step);
 
    return 0;
}