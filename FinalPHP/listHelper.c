#include "listio.h"

char *spaceMove(char *str){
	int i, spPlus=0;
	char *holder;

	holder = malloc(sizeof(char) * strlen(str)+20);
	//holder[0] = '\0';
	strcpy(holder, "");

	for(i=0; i<strlen(str)+1; i++, spPlus++){
		if(str[i] == ' ' && str[i+1] == ' '){
			strcat(holder, " ");
			i += 1;
		}
		else if(str[i] == '\t' && str[i+1] == '\t'){
			strcat(holder, "\t");
			i += 1;
		}
		holder[spPlus] = str[i];
	}
	//strcpy(str, holder);
	free(str);

	return holder;
}

char *newLine(char *str){
	int i,j;
	char *holder;
	char *pTag = "<P>";
	char *brTag = "<BR>";
	int newL = 0;
	int spaces = 1;

	holder = malloc(strlen(str)+200);
	holder[0] = '\0';

	for(i=0; i<strlen(str)+1; i++){		
		if((str[i] == '\n' && str[i+1] != '\n' && str[i+1] != ' ') || (str[i] == '\r' && str[i+1] != '\r' && str[i+1] != ' ')){
			newL = 1;
			break;
		}
		else if((str[i] == '\n' && str[i+1] == ' ') || (str[i] == '\r' && str[i+1] == ' ')){
			j = i+1;
			while(str[j] == ' '){
				j++;
				spaces = j-i;
			}
			if(str[j] == '\n' || str[j] == '\r'){
				//printf("ynoh\n");
				//i = j;
				//spaces = j-i;
				break;
			}
			else{
				newL = 1;
				break;
			}
		}
		else if((str[i] == '\n' && str[i+1] == '\n') || (str[i] == '\r' && str[i+1] == '\r') || (str[i] == '\n' && str[i+1] == '\r')){
			//printf("yeah\n");
			break;
		}
	}
	if(newL){
		strncpy(holder, str, i);
		holder[i] = '\0';
		//printf("^%s^\n", holder);
		strcat(holder, brTag);
		for(j=i+1; j<strlen(str)+1; j++){
			holder[j+3] = str[j];
		}
	}
	else{
		strncpy(holder, str, i);
		holder[i] = '\0';
		//printf("^%s^\n", holder);
		strcat(holder, pTag);
		for(j=i+1; j<strlen(str)+1; j++){
			holder[j+2] = str[j+spaces];
		}
		
	}

	/*remember if write and readstrings is tested this can cause a double free
	**corruption*/
	free(str);
	return holder;
}

void fileEdit(char *args[], FILE *fp){
	int i;
	char *find;
	FILE *untaggedFp;
	
	// FILE *fpName;
	// char *line;
	// struct returnStruct *header;
	// char *name;

	char *taggedFp;
	char buffer[4096];

	// header = buildHeader();
	// setName(header->header, fp);
	// name = getName(header->header);
	// fp = fopen(argv[1], "r");

	find = strchr(args[1], '.');
		//find is to see if the file has a '.' in it or not
	if(find){
		for(i=0; i<strlen(args[1])+1; i++){
		//printf("%c\n", args[1][i]);	
			if(args[1][i] == '.' ){
				if(args[1][i+1] == 'h' && args[1][i+2] == 't' && args[1][i+3] == 'm' && args[1][i+4] == 'l'){
					
				}
				//if it has a '.' but not html then format to html
				else if(args[1][i+1] != 'h'){
					/*read file (using a1 i believe), processString(), save it to a text file and 
					**tag it with .html end then print to stdout; use filename for name in header struct*/

					//start here:
					//after the file (without .html) is processString()'d and stuf then we continue from args[1][i+1] to finish

					args[1][i+1] = '\0';
					taggedFp = strcat(args[1], "html");
					untaggedFp = fopen(taggedFp, "w");
					while(fgets(buffer, 4096, fp) != NULL){
						fputs(buffer, untaggedFp);
					}
					fclose(untaggedFp);
					printf("%s\n", taggedFp);
				}
			}
		}
	}
	//if it does not have a '.' then it's a plain file 
	else{
		//start here:
		//after the file (without .html) is processString()'d and stuf then we continue from taggedFp=strcat to finish
		taggedFp = strcat(args[1], ".html");
		untaggedFp = fopen(taggedFp, "w");
		while(fgets(buffer, 4096, fp) != NULL){
			fputs(buffer, untaggedFp);
		}
		fclose(untaggedFp);
		printf("%s\n", taggedFp);
	}
}
