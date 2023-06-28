#include <Windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "F:\dev\dataStructures\linkedList\linkedlist.h"
#include "helpText.h"

#define str(name, len) char name[len]; memset(name, 0, len);

#define DELIM ";"

#define KIBIBYTE (1<<10)
#define MIBIBYTE (1<<20)
#define GIBIBYTE (1<<30)

typedef enum{
    NO_FILL,
    CONSTANT_FILL,
    RANDOM_BIN_FILL,
    RANDOM_TEXT_FILL
} FillTypelst;

struct appSettings{
    bool verbose;
    bool helpText;
    bool fillTypeSet;
    bool dryrun;
    FillTypelst fillType; 
    unsigned long fileSize;
    linkedList_t* fileNames;
};

struct appSettings settings;

#define between(x, a, b) ((x >= a) && (x <= b))

/**
 * @brief count the number of char occourances in a string
 * 
 * @param str string
 * @param c char to find
 * 
 * @return int -1 if str is null, otherwise the number of time the char c appears in the string
 */
int strcntc(const char* str, char c){
    int cnt = 0;

    if(str == NULL) return -1;

    for(int idx=0; idx < strlen(str); idx++){
        if(str[idx]==c) cnt++;
    }
    return cnt;
}

void parseInput(const char* argString, struct appSettings* settings){

    
    //Parse a random binary command
    if(strstr(argString, "-Rb") == argString){
        settings->fillType = RANDOM_BIN_FILL;
    }
    else if(strstr(argString, "-Rt") == argString){
        settings->fillType = RANDOM_TEXT_FILL;
    }
    else if(strstr(argString, "-v") == argString){
        settings->verbose = true;
        return;
    }
    else if(strstr(argString, "-h") == argString){
        settings->helpText = true;
        return;
    }else if(strstr(argString, "-d") == argString){
        settings->dryrun = true;
        return;
    }

    //if there is a random type present and no other one has been set
    if(((settings->fillType == RANDOM_BIN_FILL) || (settings->fillType == RANDOM_TEXT_FILL)) && (settings->fillTypeSet == false)){

        unsigned long bytecnt = (unsigned long)atol(&argString[3]);
        char last_c = argString[strlen(argString)-1];

        switch(last_c){
            case 'K': bytecnt *= KIBIBYTE; break;
            case 'M': bytecnt *= MIBIBYTE; break;
            case 'G': bytecnt *= GIBIBYTE; break;
        }

        settings->fileSize = bytecnt;
        settings->fillTypeSet = true;
        return;
    }

    //IF the string ends with ']' and contains '['
    if(((argString[strlen(argString)-1])==']') && (NULL != strrchr(argString, '['))){

        str(fileName, FILENAME_MAX);
        char* listStart = strrchr(argString, '[')+1;
        char* token = strtok(listStart, DELIM);
        
        while(token != NULL){

            int namePortion = (listStart-argString)-1;

            strncat(fileName, argString, namePortion);
            strcat(fileName, token);

            if(fileName[strlen(fileName)-1]==']'){
                fileName[strlen(fileName)-1]='\0';
            }

            lladd(settings->fileNames, strlen(fileName)+1, fileName);

            token = strtok(NULL, DELIM);
            memset(fileName, 0, FILENAME_MAX);
        }
    }
    else{
        lladd(settings->fileNames, strlen(argString)+1, argString);
    }

}

int MakeFiles(void* filename){
    HANDLE hfile = CreateFile((char*)filename, (GENERIC_READ | GENERIC_WRITE), 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

    if((hfile == INVALID_HANDLE_VALUE) && (settings.verbose)){
        printf("File \"%s\" could not be made, it may already exist.\n", (char*)filename);
    }else if(settings.verbose){
        printf("Generating file \"%s\"\n", (char*)filename);
    }

    DWORD written;
    
    srand(time(NULL));

    if(settings.fillTypeSet){
        unsigned char x;
        for(int byte = 0; byte < settings.fileSize; byte++){
            x = rand() & 0xFF;
            
            while((settings.fillType == RANDOM_TEXT_FILL) && !((x==' ') || (x=='\n') || between(x, 'a', 'z') || between(x, 'A', 'Z'))){
                x = rand() & 0xFF;
            }
            
            WriteFile(hfile, &x, 1, &written, NULL);
        }
    }

    CloseHandle(hfile);
    return 0;
}



    

int main(int argc, char* argv[]){

    memset(&settings, 0, sizeof(settings));

    settings.fileNames = llcreate();
    

    for(int arg = 1; arg < argc; arg++){
        parseInput(argv[arg], &settings);
    }


    //here's the meat of the application
    if(settings.helpText){
        printf("%s", help);
    }else{
        llforEach(settings.fileNames, MakeFiles, NULL);
    }

    //cleanup
    lldestroy(settings.fileNames);
}