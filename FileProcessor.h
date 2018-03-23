#ifndef FileProcessor_h
#define FileProcessor_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashMap.h"
#include "FileList.h"

typedef struct fileProcessElement {
    char*   rootFolder;
    char*   fileName;
    struct fileProcessElement* next;
} FileProcessElement;



void readAllFiles(char* rootFolder, struct HashNode* map);
void readFile(char* fullPathToFile,  FileProcessElement* root,struct HashNode* map);

FileProcessElement* recursiveFileGather(char* rootDirFile,  FileProcessElement* addHere);
void printFileElements( FileProcessElement* root);
char* getFileName(char* rootDirFile);

#endif /* FileList_h */
