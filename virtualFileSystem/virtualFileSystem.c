#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char commandBuf1[10];
char commandBuf2[512];
char tokenBuf[20];
int removeCount = 0;

struct directoryFile{
    char directoryFileName[20];
    struct directoryFile * parent;
    struct directoryFile * leftistChildDynamicTable;
    int leftistChildDynamicTableSize;
    int currentChildNum;
};


void initializeRoot(struct directoryFile * root){
    strcpy(root -> directoryFileName, "~");
    root -> parent = root;
    root -> leftistChildDynamicTable = NULL;
    root -> leftistChildDynamicTableSize = 0;
    root -> currentChildNum = 0;
}

void dynamicTableExpand(struct directoryFile ** oldDynamicTable, int oldDynamicTableSize){
    //double the old dynamic table size
    struct directoryFile * newDynamicTable = (struct directoryFile *) malloc(sizeof(struct directoryFile) * (oldDynamicTableSize << 1));
    //memory copy
    for(int i = 0; i < oldDynamicTableSize; i++){
        newDynamicTable[i] = (*oldDynamicTable)[i];
    }
    free(*oldDynamicTable);
    *oldDynamicTable = newDynamicTable;
}

void bornAChildDirectory(struct directoryFile * currentWorkingDirectory, char * inputFileName){
    if(!(currentWorkingDirectory -> currentChildNum)){     //doesn't exist children
        //update cuurent working directory's information
        currentWorkingDirectory -> leftistChildDynamicTable = (struct directoryFile *) malloc(sizeof(struct directoryFile) * (1 << 2));
        currentWorkingDirectory -> leftistChildDynamicTableSize = (1 << 2);
        currentWorkingDirectory -> currentChildNum = 1;

        //update child's information
        strcpy(currentWorkingDirectory -> leftistChildDynamicTable -> directoryFileName, inputFileName); 
        currentWorkingDirectory -> leftistChildDynamicTable -> parent = currentWorkingDirectory;
        currentWorkingDirectory -> leftistChildDynamicTable -> leftistChildDynamicTable = NULL;
        currentWorkingDirectory -> leftistChildDynamicTable -> leftistChildDynamicTableSize = 0;
        currentWorkingDirectory -> leftistChildDynamicTable -> currentChildNum = 0;
    }else{                                              //exist children
        for(int i = 0; i < currentWorkingDirectory -> currentChildNum; i++){
            if(!strcmp((currentWorkingDirectory -> leftistChildDynamicTable + i) -> directoryFileName, inputFileName)){
                printf("the directory %s exists\n", inputFileName);
                exit(0);
            }
        }

        if(currentWorkingDirectory -> currentChildNum == currentWorkingDirectory -> leftistChildDynamicTableSize){
            dynamicTableExpand(&(currentWorkingDirectory -> leftistChildDynamicTable), currentWorkingDirectory -> leftistChildDynamicTableSize);
            currentWorkingDirectory -> leftistChildDynamicTableSize = currentWorkingDirectory -> leftistChildDynamicTableSize << 1; 
        }
        currentWorkingDirectory -> currentChildNum ++;

        strcpy((currentWorkingDirectory -> leftistChildDynamicTable + currentWorkingDirectory -> currentChildNum - 1) -> directoryFileName, inputFileName);
        (currentWorkingDirectory -> leftistChildDynamicTable + currentWorkingDirectory -> currentChildNum - 1) -> parent = currentWorkingDirectory;
        (currentWorkingDirectory -> leftistChildDynamicTable + currentWorkingDirectory -> currentChildNum - 1) -> leftistChildDynamicTable = NULL;
        (currentWorkingDirectory -> leftistChildDynamicTable + currentWorkingDirectory -> currentChildNum - 1) -> leftistChildDynamicTableSize = 0;
        (currentWorkingDirectory -> leftistChildDynamicTable + currentWorkingDirectory -> currentChildNum - 1) -> currentChildNum = 0;        
    }
}

void changeWorkingDirectory(struct directoryFile ** currentWorkingDirectory){
    //parsing commandBuf2
    int commandBuf2Index, tokenBufIndex;
    commandBuf2Index = 0;
    while(true){
        tokenBufIndex = 0;
        while(commandBuf2[commandBuf2Index] != '\0' && commandBuf2[commandBuf2Index] != '/'){
            tokenBuf[tokenBufIndex] = commandBuf2[commandBuf2Index];
            tokenBufIndex++;
            commandBuf2Index++;       
        }
        tokenBuf[tokenBufIndex] = '\0';
        commandBuf2Index++;

        //change to next directory
        if(!strcmp(tokenBuf, "..")){
            *currentWorkingDirectory = (*currentWorkingDirectory) -> parent;
        }else{
            bool findNextDirectory;
            findNextDirectory = false;
            for(int i = 0; i < (*currentWorkingDirectory) -> currentChildNum; i++){
                if(!strcmp(((*currentWorkingDirectory) -> leftistChildDynamicTable + i) -> directoryFileName, tokenBuf)){
                    findNextDirectory = true;
                    *currentWorkingDirectory = (*currentWorkingDirectory) -> leftistChildDynamicTable + i;
                    break;
                }
            }
            if(!findNextDirectory){
                printf("the directory %s doesn't exist\n", tokenBuf);
                exit(0);
            }
        }

        //terminate parsing commandBuf2
        if(commandBuf2[commandBuf2Index - 1] == '\0'){
            break;
        }
    }
    
}

void recursivelyRemoveDirectory(struct directoryFile * removeWorkingDirectory){
    //a self-remove process
    //we should record the remove count
    struct directoryFile * removePointer;
    removePointer = removeWorkingDirectory -> leftistChildDynamicTable;

    if(!removePointer){
        return;
    }

    while(removePointer != removeWorkingDirectory){
        while(removePointer != (removePointer -> parent -> leftistChildDynamicTable + removePointer -> parent -> currentChildNum)){
            if(removePointer -> leftistChildDynamicTable != NULL){
                removePointer = removePointer -> leftistChildDynamicTable;
            }else{
                if((removePointer + 1) == (removePointer -> parent ->leftistChildDynamicTable + removePointer -> parent -> currentChildNum)){
                    removePointer++;
                    break;
                }
                removePointer++;
            }
        }
        /*
        if(removePointer -> leftistChildDynamicTable != NULL){
            removePointer = removePointer -> leftistChildDynamicTable;
            break;
        }
        */
        removePointer--;
        removePointer = removePointer -> parent;
        free(removePointer -> leftistChildDynamicTable);
        removePointer -> leftistChildDynamicTable = NULL;
        removeCount += removePointer -> currentChildNum;
        if(removePointer == removeWorkingDirectory){
            break;
        }
    }
    //just deallocate all current working directory's dynamic table and all children's memory ,but evetually doesn't deallocate current working directory
    //itself.Also,working directory's data structure is unuseful.See the next adjustAfterRemoveDirectory function. 
}

void adjustAfterRemoveDirectory(struct directoryFile * removeWorkingDirectory){
    //this directory is unuseful;
    struct directoryFile * parent = removeWorkingDirectory -> parent;
    if(removeWorkingDirectory != (parent -> leftistChildDynamicTable + parent -> currentChildNum - 1)){
        struct directoryFile * i;
        for(i = removeWorkingDirectory; i != (parent -> leftistChildDynamicTable + parent -> currentChildNum - 2); i++){
            *i = *(i + 1);
        }
        *i = *(i + 1);
    }
    parent -> currentChildNum --;
    removeCount++;
}

void removeDirectory(struct directoryFile * currentWorkingDirectory){
    for(int i = 0; i < currentWorkingDirectory -> currentChildNum; i++){
        if(!strcmp((currentWorkingDirectory -> leftistChildDynamicTable + i) -> directoryFileName, commandBuf2)){
            recursivelyRemoveDirectory(currentWorkingDirectory -> leftistChildDynamicTable + i);
            adjustAfterRemoveDirectory(currentWorkingDirectory -> leftistChildDynamicTable + i);
            return;
        }
    }
    printf("the directory %s doesn't exist\n", commandBuf2);
    exit(0);
}

void parsing_and_action(struct directoryFile ** currentWorkingDirectory){
    //parsing the command
    scanf("%s%s", commandBuf1, commandBuf2);
    if(!strcmp(commandBuf1, "mkdir")){
        bornAChildDirectory(*currentWorkingDirectory, commandBuf2);
    }else if(!strcmp(commandBuf1, "cd")){
        changeWorkingDirectory(currentWorkingDirectory);
    }else if(!strcmp(commandBuf1, "rm")){
        removeDirectory(*currentWorkingDirectory);
    }
}


int main(int argc, char ** argv){
    int commandCount;
    struct directoryFile * root, * currentWorkingDirectory;
    scanf("%d", &commandCount);
    
    root = (struct directoryFile *) malloc(sizeof(struct directoryFile));
    initializeRoot(root);
    currentWorkingDirectory = root;

    for(int i = 0; i < commandCount; i++){
        parsing_and_action(&currentWorkingDirectory);
    }
    printf("%d\n", removeCount);
    return 0;
}