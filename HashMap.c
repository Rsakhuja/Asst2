//
//  HashMap.c
//  Asst2New
//
//  Created by Ridhima Sakhuja on 3/12/18.
//  Copyright © 2018 Ridhima Sakhuja. All rights reserved.
//


#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "HashMap.h"


//void initializeRoot(){
//    root = (HashNode*)malloc(sizeof(HashNode));
//    root->word = "root";
//    root->frequency = 0;
//    puts("Memory initialized");
//}

 struct HashNode* checkWord(char* word,  struct HashNode* root){
     struct HashNode* ptr = root->next;
    while(ptr != NULL){
        int difference = strcmp(ptr->word,word);
        if(difference == 0) return ptr;
        ptr = ptr->next;
    }
    //puts("Word not found");
    return NULL;
}

 struct HashNode* insertNode(char* word, char* fileName, struct HashNode* root) {
   struct HashNode* ptr = checkWord(word,root);
    if(ptr == NULL){
         struct HashNode *newNode;
        newNode = (struct HashNode*) malloc(sizeof( struct HashNode));
        newNode -> word = word;
        newNode ->next = NULL;
        newNode ->fileElement = NULL;
        insertSorted(newNode,root);
        if(!root->next)root->next = newNode;
        //printf("%s word inserted   %s\n", fileName, word);
        ptr = newNode;
    }
    addFileElement(ptr, fileName);
    return ptr;
}

void insertSorted( struct HashNode* newNode,  struct HashNode* root){
     struct HashNode *prev;
    prev = root->next;
     struct HashNode *currPtr;
    currPtr = root->next;
    
    if(currPtr == NULL){
        root->next = newNode;
        return;
    }
    
    if(root->next && strcasecmp(newNode->word,root->next->word )<0){
        root->next = newNode;
        newNode->next = currPtr;
        return;
    }
    
    
    while(currPtr != NULL){
        
        if ( strcasecmp(prev->word,newNode->word) < 0 && strcasecmp(currPtr->word,newNode->word) >0 ) {
            prev->next = newNode;
            newNode->next = currPtr;
            
            return;
        }
        
        prev = currPtr;
        currPtr = currPtr->next;
    }
    prev->next=newNode;
}

void printNodes( struct HashNode *root,char* outputFile){
     struct HashNode *ptr = root->next;
    int i = 0;
    FILE *fp;
    fp = fopen(outputFile, "w");

    fputs("<?xml version = \"1.0\" encoding= \"UTF-8\"?>",fp);
    fputs("<fileIndex>",fp);
    while(ptr){
        i++;
        fprintf(fp,"\t<word text =\"%s\">\n", ptr->word);
        printFiles(ptr,fp);
       fputs("\t</word>",fp);
        ptr = ptr->next;
    }
    fputs("</fileIndex>",fp);
    fclose(fp);
}

char*  printXML( struct HashNode* map){

    return NULL;
}

void tokenize(char *word, char* file, struct HashNode* root){
    //   printf("BEFORE 1=%s\n",word);
    int index = 0;
    while(word[index] != '\0'){
        if(!isalnum(word[index])){
            word[index] = ' ';
        }
        index ++;
    // if(word[i] is not alphanumeric) replace with 'space'

        //Use strto with 'space' as delimiter
    }
    // printf("BEFORE 2=%s\n",word);
    //puts(word);

    char* token = strtok(word," ");
    // printf("%s\n",token);
   while(token != NULL){
       // Copy the token by mallocing then use the malloced in insert
       char* buffer = malloc(sizeof(token));
       strcpy(buffer,token);
       insertNode(buffer,file,root);
       token = strtok(NULL, " ");
    //    printf("TOK=%s\n", token);
   }

}

