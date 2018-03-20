//
//  HashMap.h
//  Asst2New
//
//  Created by Ridhima Sakhuja on 3/12/18.
//  Copyright © 2018 Ridhima Sakhuja. All rights reserved.
//

#ifndef HashMap_h
#define HashMap_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


struct HashNode  {
    char* word;
    struct FileListElement* fileElement;
    struct HashNode* next; //pointer to next node
};


//static HashNode* root;

void initializeRoot(void);
struct HashNode* checkWord(char* word, struct HashNode* root);
struct HashNode* insertNode(char* word, char* filename, struct HashNode* root);
void insertSorted( struct HashNode* newNode, struct  HashNode* root);
void printNodes( struct HashNode *root,char* outputFile);
void tokenize(char* word, char* filename, struct HashNode* root);
char* printXML(struct HashNode *map);

#endif /* HashMap_h */
