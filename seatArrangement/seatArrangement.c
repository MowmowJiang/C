#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

//L
int L;

//txt name
char txtName[15];

//txt file structure pointer
FILE * fp;

//first table for record initail txt data 
struct node1{
    char name[22];
    int position;
};
struct node1 firstTable[15000];
int firstTableIndex = 0;

//fd for txt file for future write
int fd;
int currentFileOffset;
bool firstWrite = true;

//available seat
bool * availableSeat;

//another info
bool is_txt_has_any_record = true;
bool ever_write = false;
//bool last_write = false;

void parsing_the_txt(){
    //parse and store in firstTable
    char line[31];
    fp = fopen(txtName, "r");
    while(fgets(line, 31, fp) != NULL){
        sscanf(line, "%s%d", firstTable[firstTableIndex].name, &(firstTable[firstTableIndex].position));
        firstTableIndex++;
    }
    firstTableIndex--;
    if(firstTableIndex < 0){
        is_txt_has_any_record = false;
    }
}

void sort_the_firstTable(){
    int i, j;
    struct node1 tmp;
    for(i = 1; i <= firstTableIndex; i++){
        tmp = *(firstTable + i);
        for(j = i; j > 0; j--){
            if(tmp.position < (firstTable + j - 1) -> position){
                *(firstTable + j) = *(firstTable + j - 1);
            }else{
                break;
            }
        }
        *(firstTable + j) = tmp;
    }
}

void update_the_availableSeat(){
    for(int i = 0; i <= firstTableIndex; i++){
        availableSeat[firstTable[i].position] = false;
    }
}

void find_seat(char * name, int buySeatCount, int wantContinuousSeat){
    char writeBuffer[30];
    bool find;
    find = false;
    if(buySeatCount == 1){
        for(int i = 1; i <= L; i++){
            if(availableSeat[i] == true){
                availableSeat[i] = false;
                find = true;
                printf("%d\n", i);
                //write to txt
                if(firstWrite){
                    if(is_txt_has_any_record){
                        //write(fd, "\n", 1);
                    }
                    firstWrite = false;
                }
                sprintf(writeBuffer, "%s %d\n", name, i);
                write(fd, writeBuffer, strlen(writeBuffer));
                ever_write = true;
                break;
            }
        }
        if(!find){
            printf("No seats left !\n");
        }
    }else{
        if(wantContinuousSeat){//contiguous
            int continuousCount = 0;
            for(int i = 1; i <= L; i++){
                if(availableSeat[i]){
                    continuousCount++;
                    if(continuousCount >= buySeatCount){
                        for(int j = 0; j < buySeatCount; j++){
                            availableSeat[i - buySeatCount + 1 + j] = false;
                            if(j == (buySeatCount - 1)){
                                printf("%d\n", i - buySeatCount + 1 + j);
                            }else{
                                printf("%d ", i - buySeatCount + 1 + j);
                            }
                            if(firstWrite){
                                if(is_txt_has_any_record){
                                    //write(fd, "\n", 1);
                                }
                                firstWrite = false;
                            }
                            sprintf(writeBuffer, "%s %d\n", name, i - buySeatCount + 1 + j);
                            write(fd, writeBuffer, strlen(writeBuffer));
                            ever_write = true;
                        }
                        find = true;
                        break;
                    }
                }else{
                    continuousCount = 0;
                }
            }
            if(!find){
                printf("No seats left !\n");
            }
        }else{//no contiguous
            //bool success = false;
            int tmpBuySeatCount = buySeatCount;
            //try
            for(int i = 1; i <= L; i++){
                if(availableSeat[i]){
                    tmpBuySeatCount--;
                }
            }

            if(tmpBuySeatCount <= 0){
                tmpBuySeatCount = buySeatCount;
                for(int i = 1; i <= L; i++){
                    if(tmpBuySeatCount <= 0){
                        break;
                    }
                    if(availableSeat[i]){
                        availableSeat[i] = false;
                        if(tmpBuySeatCount == 1){
                            printf("%d\n", i);
                        }else{
                            printf("%d ", i);
                        }
                        if(firstWrite){
                            if(is_txt_has_any_record){
                                //write(fd, "\n", 1);
                            }
                            firstWrite = false;
                        }
                        sprintf(writeBuffer, "%s %d\n", name, i);
                        write(fd, writeBuffer, strlen(writeBuffer));
                        ever_write = true;
                        tmpBuySeatCount--;
                    }
                }    
            }else{
                printf("No seats left !\n");
            }
        }
    }
}

void sequential_parsing(){
    char name[22];
    int buySeatCount, wantContinuousSeat;
    while(1){
        if(scanf("%s", name) == EOF){
            break;
        }else if(scanf("%d", &buySeatCount) == EOF){
            break;
        }
        if(buySeatCount > 1){
            scanf("%d", &wantContinuousSeat);
        }
        find_seat(name, buySeatCount, wantContinuousSeat);
    }
    if(ever_write){
        //lseek(fd, -1, SEEK_CUR);
        //write(fd, "\0", 1);
    }
}

int main(int argc, char ** argv){
    scanf("%s%d", txtName, &L);
    //open the txt for future write
    fd = open(txtName, O_WRONLY | O_APPEND);
    //currentFileOffset = lseek(fd, 0, SEEK_CUR);

    //malloc available seat for L + 1 size : 0 ~ L
    availableSeat = (bool *) malloc(sizeof(bool) * (L + 1));
    //init the available seat
    for(int i = 0; i <= L; i++){
        availableSeat[i] = true;
    }


    parsing_the_txt();
    sort_the_firstTable();
    update_the_availableSeat();
    sequential_parsing();

    
    return 0;
}