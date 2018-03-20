
#include <stdio.h>
#include <stdlib.h>

#include <strings.h>

#include <dirent.h>

#include "FileProcessor.h"



int main(int argc, const char* argv[]){
    //Usage: 
    // if(argc != 3){
    //         printf("Too many arguments. Only two are expected \n");
    //         printf("Usage: invertedIndex rootDirFile \n");
        
    //     exit(1);
    // }
    char* outputFile = argv[1];
    char* rootDirFile = argv[2];

    struct HashNode* map;
    map = (struct HashNode*)malloc(sizeof(struct HashNode));
    map->next = NULL;
    map->fileElement = NULL;
    map ->word = NULL;
    
    FileProcessElement* root = (FileProcessElement*)malloc(sizeof(FileProcessElement));
    root->fileName = NULL;
    root->next = NULL;
    root = recursiveFileGather(rootDirFile,root);
    readFile(rootDirFile,root,map);
    printNodes(map,outputFile);
}


