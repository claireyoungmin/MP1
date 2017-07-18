#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sample.h"
#include "sample5.h"
#include "sample7.h"

void PrintAll(FILE*, FILE*, char*);
int CheckIfSubstring(char *, char *);

int main (){

    FILE *fp1, *fp2;

    char FileList[900];

    fp1 = fopen("ORQUILLAS_MP1A.c", "r");
    fp2 = fopen("Orquillas_MP1A.out", "w+");

    PrintAll(fp1, fp2, FileList);

    fclose(fp1);
    fclose(fp2);

    return 0;

}
void PrintAll(FILE* in, FILE* out, char *str){

    FILE *newfile;
    char c, filename[60];
    int i = 0, j =0, checker;
    do{
        c = fgetc(in);
        if(c == 35){
            checker = 0;
            j = 0;
            while (c!='\n'){
                c = fgetc(in);
                j++;
                if (c == '"'){
                    checker ++;
                    c = fgetc(in);
                    i=0;
                    while(c!='"'){
                        filename[i]= c;
                        c = fgetc(in);
                        i++;
                    }
                    filename[i]='\0';
                    if(CheckIfSubstring(str, filename) == 1) {
                        strcat(str, filename);
                        newfile = fopen(filename, "r");
                        PrintAll(newfile,out, str);
                    }
                    break;
                }
            }
            if(checker == 0){
                fseek(in, -j-2, SEEK_CUR);
                c =  fgetc(in);
                fputc(c, out);
            }

            else{
                fseek(in, -i+j, SEEK_CUR);
                c = fgetc(in);
            }
        }

        if(c != 35 && c != EOF)
            fputc(c, out);

   } while (!feof(in));
}

int CheckIfSubstring(char* bigStr, char* smallStr){
    int bigLength, smallLength, i, j, ctr;

    bigLength = strlen(bigStr);
    smallLength = strlen(smallStr);


    for(i = 0; i<bigLength; i++){

        if (bigStr[i] == smallStr[0]) {
            for (j = 0; j<smallLength && smallStr[j]==bigStr[i + j]; j++);
            if (j == smallLength)
                return 0;

        }
    }

    return 1;

}
