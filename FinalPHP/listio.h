#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#define SUCCESS 1
#define FAILURE 0

struct dataHeader{
	char *name; //overall title of text
	int length; //length of TOTAL # of chars in entire text
	struct dataString *next; //points to first dataString
};
typedef struct dataHeader dHead;


struct dataString{
	char *string; //stores the data
	struct dataString *next; //points to next dataString
};
typedef struct dataString dString;

struct returnStruct{
	int value;
	struct dataHeader *header;
};
typedef struct returnStruct rTurn;

/** buildHeader()
* returns dataHeader type
* dynamically allocates the struct & sets inital values of variables
**/
struct returnStruct *buildHeader();

/**
* allocates & sets title (name) string in dH struct
**/
int setName(struct dataHeader *header, char *name);

/**
* returns a pointer to the name of string in dH struct
**/
char *getName(struct dataHeader *header);

/**
* returns an INT VALUE stored in length var FROM DH struct
**/
int getLength(struct dataHeader *header);

/**
* header: first call or new dH struct, add dataString struct value directly to next pointer in header
* str: new string is stored in this var FROM DATASTRING Struct
**/
int addString(struct dataHeader *header, char *str);

/**
* prvoids all strings
**/
int printString(struct dataHeader *header);

/**
* edits the strings in the file
**/
int processStrings(struct dataHeader *header);

/**
*
**/
int writeStrings(char *filename, struct dataHeader *header);

struct returnStruct *readStrings(char *filename);

int freeStructure(struct dataHeader *header);

//int spaceMove(char *str, char delim);


char *spaceMove(char *str);

char *newLine(char *str);

void fileEdit(char *args[], FILE *fp);