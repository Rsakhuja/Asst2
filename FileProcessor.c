//
//  FilesProcess.c
//  Asst2New
//
//  Created by Ridhima Sakhuja on 3/12/18.
//  Copyright © 2018 Ridhima Sakhuja. All rights reserved.
//
// Recursively read the file names from a given directory
/**
       folder
          file1
          folder1
              file1
              file2
              folder2
                  file3
 
       function gatherFileNames(directory)
 
 directory/folder/file1
 directory/folder/folder1/file1
 directory/folder/folder1/file2
 directory/folder/folder1/folder2/file3
 
 
 */


#include <dirent.h>

#include "FileProcessor.h"

FileProcessElement* recursiveFileGather(char* rootDirFile,  FileProcessElement* root){
    DIR* d;
    struct dirent *dir;
    d = opendir(rootDirFile);
    char  folder[1024];
//    struct FileProcessElement* root = NULL;
    if(d){
        while((dir = readdir(d)) != NULL){
            if(dir->d_name[0] == '.'){
                continue;
            }
            if(dir->d_type == DT_DIR){
                // Concatenate to create the absolute path for the folder that was found
                // rootFolder = rrootDir +"/"+dir->d_name
//                rootDir = dir->d_name;
                folder[0] = '\0';
                strcat(folder, rootDirFile);
                strcat(folder,"/");
                strcat(folder, dir->d_name);
               //printf("Root %s   Sub-Folder %s\n", rootDirFile, dir->d_name);
            //    printf("%s\n",rootDir);
                
                recursiveFileGather(folder, root);
            }else{
                folder[0] = '\0';
                strcat(folder, rootDirFile);
                strcat(folder,"/");
                strcat(folder, dir->d_name);
                //printf("%s\n", dir->d_name);

                FileProcessElement *newFile;
                newFile= ( FileProcessElement*)malloc(sizeof( FileProcessElement));
                newFile->rootFolder = malloc(strlen(folder)+1);
                strcat(newFile->rootFolder,folder);
                //printf("%s\n",newFile->rootFolder);
                folder[0] = '\0';
                newFile->fileName = dir->d_name;
                //printf("Filenames: %s\n",newFile->fileName);
                newFile->next = NULL;
                
                if(root->next == NULL){
                    root->next = newFile;
                }else{
                     FileProcessElement *temp;
                    temp = root->next;
                    root->next = newFile;
                    newFile->next = temp;
                }
                
            }
        }
    } else {
        // its a file
        FileProcessElement *newFile;
        newFile= ( FileProcessElement*)malloc(sizeof( FileProcessElement));
        newFile->rootFolder = malloc(strlen(rootDirFile)+1);
        strcat(newFile->rootFolder,rootDirFile);
         //printf("%s\n",newFile->rootFolder);

        //just get file name
        // int index = strlen(rootDirFile);
        // char file[1000]; 
        // int fileIndex= 0;
        // while(rootDirFile[index] != '/'){
        //     file[fileIndex] = rootDirFile[index];
        //     fileIndex++;
        //     index --; 
        // }
        // printf("%s\n", file);
       
        // Both rootDir and file name are the same in this case so no need to have 2 sepaarte
        newFile->fileName = malloc(strlen(rootDirFile)+1);  //newFile->rootFolder;
        strcat(newFile->fileName,rootDirFile);
        newFile->next = NULL;

        root->next = newFile;


       // puts("is a file");
    }
   
    return root;
}

void readAllFiles(char* rootFolder, struct HashNode* map){
   
}

void readFile(char* filepathtofolder,  FileProcessElement* root,struct HashNode* map){
    FileProcessElement* temp;
    temp = root->next;
    while(temp){
        FILE* fptr;


        fptr = fopen(temp->rootFolder,"r");


     printf("OPEN FILE=> %s     %s\n",temp->rootFolder,temp->fileName);
       char buffer[1024];
       char *word;

        if(fptr!= NULL){
            if(feof(fptr)){
                puts("empty file");
                continue;
            }
            while(!feof(fptr)){
                fscanf(fptr,"%s",buffer);
                word = malloc(strlen(buffer)+1);
                strcat(word,buffer);
                tokenize(word,temp->fileName,map);
            }
            buffer[0]= '\0';
            fclose(fptr);
        }else{
            puts("could not open file");
        }
        temp = temp->next;
    }
}

void printFileElements( FileProcessElement* root){
    FileProcessElement* temp;
    temp = root->next;
    while(temp != NULL){
      // printf("%s    %p    %p \n",temp->fileName, (void*) temp, (void *)temp->next);
        temp = temp->next;
    }
}
