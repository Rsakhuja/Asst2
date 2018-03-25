//
//  FileProcessor.c
//  Asst2
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

//extract file name from path - only used if input folder is file instead of a directory
char* getFileName(char* rootDirFile){
        int rootIndex = strlen(rootDirFile)-1;
        char* file;

        //get index of first character after '/'
        while(rootDirFile[rootIndex] != '/'){
            //printf("%c\n", rootDirFile[index]);
            rootIndex --; 
        }
        rootIndex ++;

        //get length of file name and malloc file 
        int fileLength = (strlen(rootDirFile)-1)- rootIndex; 
        file = malloc(fileLength +1);
        int fileIndex = 0;
        // add characters from rootDirFile to file
       while(fileIndex <= fileLength){
           file[fileIndex] = rootDirFile[rootIndex];
           fileIndex ++;
           rootIndex ++;
       }
       return file; 
}

//function opens each directory and adds each file to separate linked list
FileProcessElement* recursiveFileGather(char* rootDirFile,  FileProcessElement* root){
    DIR* d;
    struct dirent *dir;
    d = opendir(rootDirFile);
    char  folder[1024]; //create buffer
    if(d){ //if it is a directory
        while((dir = readdir(d)) != NULL){
            if(strcmp(dir->d_name, ".") ==0  || strcmp(dir->d_name, "..") ==0 || strcmp(dir->d_name, ".DS_Store") ==0){
                continue;
            }
            
            // if(dir->d_name[0] == '.'){
            //     continue;
            // }
            // if(strlen(dir->d_name) == 1 && dir->d_name[0] == '.'){
            //     continue;
            // }
            // if(strlen(dir->d_name) == 2 && strcmp(dir->d_name, "..") =0){
            //     continue;
            // }
            
            if(dir->d_type == DT_DIR){
                // Create file path: concatenate to create the absolute path for the folder that was found
                // rootFolder = rrootDir +"/"+dir->d_name
//                rootDir = dir->d_name;
                folder[0] = '\0'; //reset file path before concatenating
                strcat(folder, rootDirFile);
                strcat(folder,"/");
                strcat(folder, dir->d_name);
                
                recursiveFileGather(folder, root); //call function if directory
            }else{  //otherwise add file to linked list
                folder[0] = '\0'; //reset file path
                //concatentate to create new file path
                strcat(folder, rootDirFile);
                strcat(folder,"/");
                strcat(folder, dir->d_name);

                //create new FileProcessElement and intialize
                FileProcessElement *newFile;
                newFile= ( FileProcessElement*)malloc(sizeof( FileProcessElement));
                newFile->rootFolder = malloc(strlen(folder)+1);
                strcat(newFile->rootFolder,folder);  //add folder to fqname

                folder[0] = '\0'; //reset 
                newFile->fileName = dir->d_name;
                newFile->next = NULL;
                
                if(root->next == NULL){ //if first element in linkedlist, just add to root->next
                    root->next = newFile;
                }else{ //otherwise add to front
                     FileProcessElement *temp;
                    temp = root->next;
                    root->next = newFile;
                    newFile->next = temp;
                }
                
            }
        }
    //otherwise if its a file
    } else {
        //create new FileProcessElement and intialize
        FileProcessElement *newFile;
        newFile= ( FileProcessElement*)malloc(sizeof( FileProcessElement));
        newFile->rootFolder = malloc(strlen(rootDirFile)+1);
        strcat(newFile->rootFolder,rootDirFile);
        
        //extract just file name from path and add as newFile->fileName
        char* file = getFileName(rootDirFile);
        newFile->fileName = malloc(strlen(file)+1);  
        strcat(newFile->fileName,file);
        newFile->next = NULL;

        root->next = newFile;
    }
   
    return root;
}

//iterate through linked list and read each file 
void readFile(char* filepathtofolder,  FileProcessElement* root,struct HashNode* map){
    FileProcessElement* temp;
    temp = root->next;
    //iterate and open each file
    while(temp){
        FILE* fptr;
        fptr = fopen(temp->rootFolder,"r");
     printf("OPEN FILE=> %s     %s\n",temp->rootFolder,temp->fileName);
       char buffer[1024];
       char *word;

        if(fptr!= NULL){
            if(feof(fptr)){  //if fptr is empty 
                puts("empty file");
                continue;
            }
            while(!feof(fptr)){ //otherwise add each word to map 
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

//print each file element in linked list - only used for testing purposes 
void printFileElements( FileProcessElement* root){
    FileProcessElement* temp;
    temp = root->next;
    while(temp != NULL){
      // printf("%s    %p    %p \n",temp->fileName, (void*) temp, (void *)temp->next);
        temp = temp->next;
    }
}
