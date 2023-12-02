typedef struct cell {
    int r; // row index
    int c; // column index
} Cell;
 
typedef struct weapon {
    int type;
    int atk; // attack power
    int drb; // durability
} Weapon;
 
int followLeft(int N, int maze[N][N], Cell start, Cell end, int M, Weapon weapon[M]);