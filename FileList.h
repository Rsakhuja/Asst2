//
//  FileList.h
//  Asst2New
//
//  Created by Ridhima Sakhuja on 3/12/18.
//  Copyright © 2018 Ridhima Sakhuja. All rights reserved.
//

#ifndef FileList_h
#define FileList_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashMap.h"



typedef struct FileListElement {
    char* filename;
    int frequency;
    struct FileListElement* next; //points to next file
} FileListElement;

void addFileElement(struct HashNode* ptr, char* filename);
void printFiles( struct HashNode* ptr,FILE* fp);
void sortFiles(struct HashNode* hashPtr);
void swap(FileListElement* currPtr,FileListElement* prev, FileListElement* temp,struct HashNode* hashPtr);
void sortFileList(struct HashNode* hashPtr);

#endif /* FileList_h */
