#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXTCOMPARISON 1
#define VIDEOCOMPARISON 2


struct file{
	char fileType[6];
	char fileName[5];
	
	int videoLength;
	char textContent[10];

	int fileSize;

	struct file * pre;
	struct file * next;
};

struct listInfo{
	//doubly linked-list
	struct file * List;
	int listLength;
	struct file * listHead, * listTail;
	struct file * currentListPointer;
};



void listAppend(struct listInfo * appendedList, struct file * inputInfo){
	if(!(appendedList -> List)){
		appendedList -> List = (struct file *) malloc(sizeof(struct file));
		*(appendedList -> List) = *inputInfo;
		appendedList -> listLength = 1;
		appendedList -> listHead = appendedList -> listTail = appendedList -> List;
	}else{
		struct file * tmpNode = (struct file *) malloc(sizeof(struct file));
		*tmpNode = * inputInfo;
		appendedList -> listTail -> next = tmpNode;
		tmpNode -> pre = appendedList -> listTail;
		appendedList -> listTail = appendedList -> listTail -> next;
		appendedList -> listLength = appendedList -> listLength + 1;
	}
}



void init(struct listInfo ** textList, struct listInfo ** videoList){
	*textList = (struct listInfo *) malloc(sizeof(struct listInfo));
	*videoList = (struct listInfo *) malloc(sizeof(struct listInfo));

	(*textList) -> List = (*videoList) -> List = 0x00;
	(*textList) -> listLength = (*videoList) ->listLength = 0;
	(*textList) -> listHead = (*textList) -> listTail = (*videoList) -> listHead = (*videoList) -> listTail = 0x00;
	(*textList) -> currentListPointer = (*videoList) -> currentListPointer = 0x00;
}

int comparison(int comparisonMode, struct file * node1, struct file * node2){
	int tmp;
	if(comparisonMode == TEXTCOMPARISON){
		if((tmp = strcmp(node1 -> textContent, node2 -> textContent)) != 0){
			return tmp;
		}else if((tmp = node1 -> fileSize - node2 -> fileSize) != 0){
			return tmp;
		}else if((tmp = strcmp(node1 -> fileName, node2 -> fileName)) != 0){
			return tmp;
		}else{
			return 0;
		}
	}else{
		if((tmp = node1 -> videoLength - node2 -> videoLength) != 0){
			return tmp;
		}else if((tmp = node1 -> fileSize - node2 -> fileSize) != 0){
			return tmp;
		}else if((tmp = strcmp(node1 -> fileName, node2 -> fileName)) != 0){
			return tmp;
		}else{
			return 0;
		}
	}
}

void insertion(struct listInfo * insertedListInfo, struct file * loopj){
	struct file * tmpNode = loopj;
	struct file * comparedNode = tmpNode;
	int comparisonMode;
	if(!strcmp(insertedListInfo -> List -> fileType, "text")){
		comparisonMode = TEXTCOMPARISON;
	}else{
		comparisonMode = VIDEOCOMPARISON;
	}

	while(tmpNode -> next != 0x00 && (comparison(comparisonMode, comparedNode, tmpNode -> next) < 0)){
		tmpNode = tmpNode -> next;
	}

	if(loopj == tmpNode) return;

	if(loopj != insertedListInfo -> listHead){
		loopj -> pre -> next = loopj -> next;
		loopj -> next -> pre = loopj -> pre;
		if(tmpNode -> next != 0x00){
			loopj -> pre = tmpNode;
			loopj -> next = tmpNode -> next;
			loopj -> pre -> next = loopj -> next -> pre = loopj;
		}else{
			tmpNode -> next = loopj;
			loopj -> pre = tmpNode;
			loopj -> next = 0x00;
			insertedListInfo -> listTail = loopj;	
		}
	}else{
		insertedListInfo -> listHead = loopj -> next;
		loopj -> next -> pre = 0x00;
		if(tmpNode -> next != 0x00){
			loopj -> next = tmpNode -> next;
			loopj -> next -> pre = loopj;
			loopj -> pre = tmpNode;
			loopj -> pre -> next = loopj;
		}else{
			tmpNode -> next = loopj;
			loopj -> pre = tmpNode;
			loopj -> next = 0x00;
			insertedListInfo -> listTail = loopj;
		}
	}
}

void listInsertSort(struct listInfo * insertedListInfo){
      if(insertedListInfo -> listLength > 1){
		struct file * loopi, * loopj;	
		struct file * loopiPre;      
		loopi = insertedListInfo -> listTail -> pre;
		loopiPre = loopi -> pre;
		while(loopi != insertedListInfo -> listHead){
			insertion(insertedListInfo, loopi);
			loopi = loopiPre;
			loopiPre = loopi -> pre;
		}
		insertion(insertedListInfo, loopi);
	}
}

void Print(struct listInfo * textList, struct listInfo * videoList, int x, int y){
	struct file * traversal;
	traversal = textList -> listTail;
	--x;
	while(traversal != 0x00 && x != 0){
		--x;
		traversal = traversal -> pre;
	}
	if(traversal != 0x00){
		printf("%s ", traversal -> fileName);
	}else{
		printf("DNE ");
	}

	traversal = videoList -> listTail;
	--y;
	while(traversal != 0x00 && y != 0){
		--y;
		traversal = traversal -> pre;
	}
	if(traversal != 0x00){
		printf("%s\n", traversal -> fileName);
	}else{
		printf("DNE\n");
	}
}

int main(int argc, char ** argv){
	int n;
	struct listInfo * textList, * videoList;
	struct file inputInfo;
	int x, y;
	init(&textList, &videoList);
		
	scanf("%d", &n);
	
	for(int i = 0; i < n; i++){
		scanf("%s", inputInfo.fileType);
		scanf("%s", inputInfo.fileName);
		if(!strcmp(inputInfo.fileType, "text")){
			scanf("%s", inputInfo.textContent);
		}else{
			scanf("%d", &(inputInfo.videoLength));
		}					
		scanf("%d", &(inputInfo.fileSize));
		inputInfo.pre = inputInfo.next = 0x00;

		if(!strcmp(inputInfo.fileType, "text")){
			listAppend(textList, &inputInfo);
		}else{
			listAppend(videoList, &inputInfo);
		}
	}

	scanf("%d%d", &x, &y);
	listInsertSort(textList);
	listInsertSort(videoList);
	Print(textList, videoList, x, y);
	return 0;
}










