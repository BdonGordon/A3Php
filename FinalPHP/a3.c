#include "listio.h"

int main(int argc, char *argv[]) {
	FILE *fp;
	char buffer[4096];
	struct returnStruct *header;
	char *line = malloc(sizeof(char)*4096+5);
	int i, flag=0, j, dot=0;
	char holder[4096];
	header = buildHeader();
	setName(header->header, argv[1]);
	fp = fopen(argv[1], "r");
	for(i=0; i<strlen(argv[1])+1; i++){
		holder[i] = argv[1][i];
		if(argv[1][i] == '.' ){
			if(argv[1][i+1] == 'h' && argv[1][i+2] == 't' && argv[1][i+3] == 'm' && argv[1][i+4] == 'l'){
				flag = 3;
			}
		}
	}
	for(j=0; j<strlen(holder); j++){
		if(holder[j] == '.' && flag != 3){
			dot++;
			flag = 1;
		}
	}
	//for .txt files or whatever else.
	if(flag == 1 && flag != 3 && dot>1){
		while(fgets(buffer, 4096, fp) != NULL){
			line = strcpy(line, buffer);
                        addString(header->header, line);
                }
                processStrings(header->header);
	}
	//for regular degular files with no extentions (ie. bwoi)
	else if(flag != 3){
		while(fgets(buffer, 4096, fp) != NULL){
                	line = malloc(strlen(buffer)+5);
                        line = strcpy(line, buffer);
			addString(header->header, line);
                }
		processStrings(header->header);
	}
	//if the .html file does not exist
	freeStructure(header->header);
	free(line);
	free(header);

	fclose(fp);

	return 0;
}
