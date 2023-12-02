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
 
    int M;
    scanf("%d", &M);
 
    Weapon weapon[M];
    for (int k = 0; k < M; k++) {
        scanf("%d%d%d", &weapon[k].type, &weapon[k].atk, &weapon[k].drb);
    }
 
    int attack = followLeft(N, maze, start, end, M, weapon);
    printf("%d\n", attack);
 
    return 0;
}