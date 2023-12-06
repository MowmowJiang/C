#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//if va

struct directoryFile{
	char directoryFileName [20];
	int currentChildNum;
	int childDynamicTableSize;
	struct directoryFile * parent;
	struct directoryFile * leftChild;			//using dynamic table
};
char * pathToBePrinted[500];
struct directoryFile * root; 					//~
struct directoryFile * currentWorkingDirectory;

void dynamicTableCreate(struct directoryFile * node, char * inputDirectoryName){
	//initialize dynamic table
	//born a child
	node -> currentChildNum = 1;
	node -> childDynamicTableSize = 4;
	node -> leftChild = (struct directoryFile *) malloc(sizeof(struct directoryFile) * 4);
	strcpy(node -> leftChild -> directoryFileName, inputDirectoryName);
	node -> leftChild -> parent = node;
	node -> leftChild -> currentChildNum = 0;
	node -> leftChild -> childDynamicTableSize = 0;
	node -> leftChild -> leftChild = 0x00;
}

void memoryCopy(struct directoryFile * src, struct directoryFile * dst, int copyNum){
	for(int i = 0; i < copyNum; i++){
		dst[i] = src[i];
	}
}

struct directoryFile * dynamicTableExpand(struct directoryFile * dynamicTable, int currentDynamicTableSize, int currentChildNum){
	struct directoryFile * newDynamicTable = (struct directoryFile *) malloc(sizeof(struct directoryFile) * (currentDynamicTableSize * 2));
	memoryCopy(dynamicTable, newDynamicTable, currentChildNum);
	free(dynamicTable);
	return newDynamicTable;
}

void dynamicTableAddSibling(struct directoryFile * parent, char * inputDirectoryName){
	if(parent -> currentChildNum == parent -> childDynamicTableSize){
		parent -> leftChild = dynamicTableExpand(parent -> leftChild, parent -> childDynamicTableSize, parent -> currentChildNum);
		parent -> childDynamicTableSize *= 2; ////////////////////
	}
	parent -> currentChildNum = parent -> currentChildNum + 1;
	strcpy(((parent -> leftChild) + ((parent -> currentChildNum) - 1)) -> directoryFileName, inputDirectoryName);
	((parent -> leftChild) + ((parent -> currentChildNum) - 1)) -> currentChildNum = 0;
	((parent -> leftChild) + ((parent -> currentChildNum) - 1)) -> childDynamicTableSize = 0;
	((parent -> leftChild) + ((parent -> currentChildNum) - 1)) -> parent = parent;
	((parent -> leftChild) + ((parent -> currentChildNum) - 1)) -> leftChild = 0x00;
	//((parent -> leftChild) + ((parent -> currentChildNum) - 1)) -> leftChild = (struct directoryFile *) malloc(sizeof(struct directoryFile) * 4);
}

bool findChild(struct directoryFile ** currentWorkingDirectory, char * givenChildName){
	char * comparedChildName;
	for(int i = 0; i < (*currentWorkingDirectory) -> currentChildNum; i++){
		comparedChildName = ((*currentWorkingDirectory) -> leftChild + i) -> directoryFileName; 
		if(!strcmp(comparedChildName, givenChildName)){
			*currentWorkingDirectory = (*currentWorkingDirectory) -> leftChild + i;
			return true;
			break;
		}
	}
	return false;
}

void traversePath(struct directoryFile ** currentWorkingDirectory, char * path){
	//parse the path
	char token[20];
	int scanningIndex = 0;
	int tokenIndex;
	//char buf[3] = "..";
	 
	while(true){
		tokenIndex = 0;
		while(*(path + scanningIndex) != '/' && *(path + scanningIndex) != '\0'){
			*(token + tokenIndex) = *(path + scanningIndex);
			++scanningIndex;
			++tokenIndex;
		}

		*(token + tokenIndex) = '\0';
		++scanningIndex;
		
		if(!strcmp(token, "..")){
			if(*currentWorkingDirectory != root){
				*currentWorkingDirectory = (*currentWorkingDirectory) -> parent;
			}
		}else{ //go child directory
			if(!findChild(currentWorkingDirectory, token)){
				printf("directory %s doesn't exist\n", token);
				exit(0);
			}
		}
		if(*(path + scanningIndex - 1) == '\0'){
			break;
		}
	}
	
}

int main(int argc, char * argv[]){
	int n;
	char buf1[20];
	char buf2[512];

	//root initialization
	root = (struct directoryFile *) malloc(sizeof(struct directoryFile));
	strcpy(root -> directoryFileName, "~");
	root -> currentChildNum = 0;
	root -> childDynamicTableSize = 0;
	root -> parent = root -> leftChild = 0x00;
	currentWorkingDirectory = root;
	
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s", buf1);
		scanf("%s", buf2);
		if(!strcmp(buf1, "mkdir")){
			for(int i = 0; i < currentWorkingDirectory -> currentChildNum; i++){
				if(!strcmp((currentWorkingDirectory -> leftChild + i) -> directoryFileName, buf2)){
					printf("directory %s has been existed\n", buf2);
					exit(0);
				}
			}
			if(!(currentWorkingDirectory -> currentChildNum)){
				dynamicTableCreate(currentWorkingDirectory, buf2);
			}else{
				dynamicTableAddSibling(currentWorkingDirectory, buf2);
			}
		}else{						//cd
			traversePath(&currentWorkingDirectory, buf2);
		}
	}
	
	//back trace and print the path
	int pathLength = 0;      									//not include root
	struct directoryFile * tmp = currentWorkingDirectory;

	
	while(tmp != root){
		pathToBePrinted[pathLength] = tmp -> directoryFileName;
		tmp = tmp -> parent;
		++pathLength;
	}
	
	if(!pathLength){
		printf("~\n");
	}else{
		printf("~");
		for(int i = pathLength - 1; i >= 0; i--){
			printf("/%s", pathToBePrinted[i]);
		}
		printf("\n");
	}
	
	return 0;
}
