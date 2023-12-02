typedef struct cell {
    int r; // row index
    int c; // column index
} Cell;
 
int followLeft(int N, int maze[N][N], Cell start, Cell end);