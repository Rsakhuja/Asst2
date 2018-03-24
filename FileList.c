//
//  FileList.c
//  Asst2
// This is a linked list implementtion
// It will have file + counter

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "FileList.h"

void addFileElement( struct HashNode* hashPtr, char* filename){
    FileListElement* filePtr;
    filePtr = hashPtr->fileElement;
    

    while(filePtr){
        if(strcmp(filePtr->filename,filename) == 0){
            filePtr->frequency++;
            return;
        }
        filePtr = filePtr ->next;
    }
    FileListElement *fileNode;
    fileNode = (FileListElement*)malloc(sizeof(FileListElement));
    fileNode->filename = filename;
    fileNode->frequency = 1;
    
    //insert to front 
    FileListElement *temp;
    temp = hashPtr->fileElement;
    hashPtr->fileElement = fileNode;
    fileNode->next = temp;
   
}
void swap(FileListElement* currPtr, FileListElement* prev,FileListElement* temp,struct HashNode* hashPtr){
    if(prev == NULL){
        hashPtr->fileElement = temp;
        temp->next = currPtr;
        currPtr->next = NULL;
        return;
    }
    prev->next = temp;
    temp->next = currPtr;
    currPtr->next = NULL;

    
}

void  swapTwo( FileListElement* node1, FileListElement* node2){

    char*  filename = node1->filename;
    int    frequency= node1->frequency;

    node1->filename = node2->filename;
    node1->frequency=node2->frequency;

    node2->filename = filename;
    node2->frequency= frequency;
    

    // FileListElement* temp = node2->next;
    // node2->next = node1->next;
    // node1->next = temp;
    // if(root == node1){
    //     puts("Swapped Root");
    //     return  node2;
    // }
    // puts("Swapped NULL");
    // return NULL;
}

void sortFiles(struct HashNode* hashPtr){


    FileListElement* prev;
    prev = hashPtr->fileElement;

    FileListElement* currPtr;
    currPtr = prev;

    while(prev != NULL){
        while(currPtr->next != NULL){
            currPtr = currPtr->next;
            printf("Check %s %i  %s %i\n", prev->filename, prev->frequency, currPtr->filename, currPtr->frequency);
            if(prev->frequency == currPtr->frequency){

                if(strcmp(prev->filename, currPtr->filename) < 0){
                    swapTwo(prev,currPtr);
                }

            } else if(prev->frequency < currPtr->frequency){ 
               swapTwo(prev,currPtr);
               
            } 
            
        }
        prev = prev->next;
        currPtr = prev;
    }

}

void printFiles( struct HashNode* ptr,FILE* fp){
    FileListElement* filePtr;
    filePtr = ptr->fileElement;
    sortFiles(ptr);
    filePtr = ptr->fileElement;
    while(filePtr){
       fprintf(fp,"\t\t<file name = \"%s\">%d</file>\n", filePtr->filename, filePtr->frequency);
        filePtr = filePtr->next;
    }
    
}
