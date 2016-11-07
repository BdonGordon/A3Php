#include "listio.h"

struct returnStruct *buildHeader(){
	dHead *dataTemp = NULL;
	rTurn *retVal = malloc(sizeof(rTurn));

	dataTemp = calloc(1, sizeof(dHead));
	//dataTemp = malloc(sizeof(dHead));
	dataTemp->name = NULL;
	dataTemp->length = 0;
	dataTemp->next = NULL;
	retVal->value = SUCCESS;
	retVal->header = dataTemp;
	//dataTemp = retVal->;

	return retVal;
}

int setName(struct dataHeader *header, char *name){
	header->name = malloc(sizeof(char)*strlen(name)+1);
	strcpy(header->name, name);

	if(header->name != NULL){
		return SUCCESS;
	}
	else{
		return FAILURE;
	}
}

char *getName(struct dataHeader *header){
	if(header->name == NULL){
		return NULL;
	}
	else{
		return header->name;
	}
}

int getLength(struct dataHeader *header){
	if(header->length == 0){
		return FAILURE;
	}
	else{
		return header->length;
	}
}

int freeStructure(struct dataHeader *header){
	struct dataString *temp;

	while(header->next != NULL){
		temp = header->next;
		header->next = header->next->next;
		free(temp->string);
		free(temp);
	}
	header->length=0;
	free(header->name);
	free(header);

	return SUCCESS;
}

int addString(struct dataHeader *header, char *str){
	struct dataString *temp = malloc(sizeof(struct dataString) * sizeof(char)); 
	struct dataString *holder;
	int strLength=0;

	temp->string = malloc(strlen(str)+1);

	temp->next = NULL;
	if(header->next == NULL){
		strcpy(temp->string, str);
		header->next = temp;
		for(strLength=0;strLength<=strlen(temp->string);strLength++);
		header->length += strLength;
	}
	else{
		//this will point to the current node so we can traverse
		holder = header->next;
		strcpy(temp->string, str);
		while(holder->next != NULL){
			holder = holder->next;
		}
		for(strLength=0;strLength<=strlen(temp->string);strLength++);
		header->length += strLength;
		holder->next = temp;
		temp->next = NULL;
	}

	if(temp->next == NULL){
		return SUCCESS;
	}
	else{
		return FAILURE;
	}
}

int printString(struct dataHeader *header){
	struct dataString *temp = NULL;

	if(header->next != NULL){
		temp = header->next;	
	}
	while(temp != NULL){
		printf("%s\n", temp->string);
		temp = temp->next;
	}

	if(temp == NULL){
		return SUCCESS;
	}
	else{
		return FAILURE;
	}
}

int processStrings(struct dataHeader *header){
	int i, j;
	struct dataString *temp;
	int strLength = 0;
	FILE *fp, *htmlFp; 
	char *taggedFp;
	char readPipeBuff[4096];
	char nextTemp[500]; //to compare if the 2 strings have <P> tags at end and beg
	int lineFlag = 0; //to notify that the newline function was used
	int tagFlag = 0; //notify that a tag was inserted into the string
	temp = header->next;
	header->length = 0; 

	char *cmd[] = {"./a3.py", "q1", "q2", header->name, NULL};

	pid_t pid;

	while(temp != NULL){
		//printf("!!!%s\n", temp->string);
		for(i=0; i<strlen(temp->string); i++){
			if(temp->string[i] == ' ' || temp->string[i] == '\t'){
				temp->string = spaceMove(temp->string);
			}
			else if(temp->string[i] == '\n' || temp->string[i] == '\r'){
				temp->string = newLine(temp->string);
				i += 3;
				lineFlag = 1;
			}
		}
		strLength = strlen(temp->string)+1;
		header->length += strLength;

		if(lineFlag == 1){
			for(j=0; j<strlen(temp->string)+1; j++){
				if(temp->string[strlen(temp->string)-1] == '>'){
					tagFlag = 1;
				}
			}
			if(tagFlag == 1 && temp->next != NULL){
				strcpy(nextTemp, temp->next->string);
				if(nextTemp[0] == '\n' && nextTemp[1] == '\n'){
					temp->string[strlen(temp->string)-3] = '\0';
					tagFlag = 0;
				}
			}
			lineFlag = 0;
		}

		//printf("shit\n");
		temp = temp->next;
	}

	pid = fork();
	if(pid == 0){
		execvp(cmd[0], cmd);
	}
	else{
		mkfifo("./files/q1", 0777);
		fp = fopen("./files/q1", "w");
		temp = header->next;
		while(temp != NULL){
			fprintf(fp, "%s\n", temp->string);
			//printf("%s\n", temp->string);
			temp = temp->next;
		}

		fclose(fp);

		mkfifo("./files/q2", 0777);
		//remove("q1");
		fp = fopen("./files/q2", "r");
		if(fp == NULL){
			printf("Error occurred while opening file. Abort.\n");
			exit(0);
		}
		else{
			taggedFp = strcat(header->name, ".html");
			htmlFp = fopen(taggedFp, "w");
			while(fgets(readPipeBuff, 4096, fp) != NULL){
				//printf("%s", readPipeBuff);
				fputs(readPipeBuff, htmlFp);
			}
			fclose(htmlFp);
		}
		fclose(fp);
		remove("./files/q2");
	}

	if(temp == NULL){
		return SUCCESS;
	}
	else{
		return FAILURE;
	}
}

int writeStrings(char *filename, struct dataHeader *header){
	FILE *fp;
	struct dataString *temp;
	char *fpString;
	char *headerName;
	int headNum=0, dataNum=0;
	int finalLength = header->length;
	fp = fopen(filename, "wb");

	if(fp == NULL){
		perror("Error occurred while opening file.\n");
		//return FAILURE;
	}
	else{
		temp = header->next;
		fpString = malloc(strlen(temp->string)+1);
		headerName = getName(header);
		headNum = strlen(headerName)+1;
		fwrite(&(headNum), 1, sizeof(int), fp);
		fwrite(headerName, strlen(headerName)+1, sizeof(char), fp);
		fwrite(&(finalLength), 1, sizeof(int), fp);

		// printf("%d\n", headNum);
		// printf("%s\n", headerName);
		// printf("%d\n", finalLength);

		while(temp != NULL){
			strcpy(fpString, temp->string);
			dataNum = strlen(fpString)+1;
			fwrite(&(dataNum), sizeof(int), 1, fp);
			fwrite(fpString, sizeof(char), strlen(fpString)+1, fp);

			// printf("%d\n", dataNum);
			// printf("%s", fpString);
			// printf("\n");

			temp = temp->next;
		}
	}
	free(fpString);
	fclose(fp);

	return SUCCESS;

}

struct returnStruct *readStrings(char *filename){
	struct returnStruct *temp = buildHeader();
	FILE *fp;
	int headLen=0, strLength=0;
	int totLen=0;
	char *tempHead;
	char *tempStr;

	fp = fopen(filename, "r");

	if(fp == NULL){
		perror("Error occurred while opening file.\n");
		temp->header = NULL;
		return temp;
	}
	else{
		fread(&(headLen), sizeof(int), 1, fp);
		tempHead = malloc(sizeof(char) * headLen+1);
		fread(tempHead, sizeof(char), headLen, fp);
		fread((&totLen), sizeof(int), 1, fp);
		//CHANGE FOR REGRADE RIGHT HERE
		//addString(temp, tempHead);

		// printf("-------------------------------------\n");
		// printf("%d\n", headLen);
		// printf("%s\n", tempHead);
		//printf("%d\n", totLen);

		while(totLen != 0){
			fread((&strLength), sizeof(int), 1, fp);
			totLen -= strLength;
			//printf("%d\n", strLength);
			tempStr = malloc(sizeof(char) * strLength+1);
			fread(tempStr, sizeof(char), strLength, fp);
			//printf("%s\n", tempStr);
			addString(temp->header, tempStr);
			free(tempStr);
		}
	}
	free(tempHead);
	fclose(fp);

	return temp;
}
