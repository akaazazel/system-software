#include <stdio.h>
#include "string.h"
#include <stdlib.h>

struct{
    char dname[10], fname[10][10];
    int fcnt;
}dir;

void main(){
    int i, ch;
    char f[30];
    dir.fcnt = 0;
    printf("Enter the name of the directory: ");
    scanf("%s", dir.dname);
    
    while(1){
        printf("1. Create | 2. Delete | 3. Search | 4. Display | 5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        
        switch(ch){
            case 1:
                printf("Enter the name of the file: ");
                scanf("%s", dir.fname[dir.fcnt]);
                printf("%s is created!\n", dir.fname[dir.fcnt]);
                dir.fcnt++;
                break;
                
            case 2:
                printf("Enter the name of the file: ");
                scanf("%s", f);
                
                for (i = 0; i < dir.fcnt; i++){
                    if(strcmp(f, dir.fname[i]) == 0){
                        printf("%s deleted!\n", f);
                        strcpy(dir.fname[i], dir.fname[dir.fcnt-1]);
                        break;
                    }
                }
                
                if(i == dir.fcnt){
                    printf("File not found!\n");
                }else{
                    dir.fcnt--;
                }
                break;
                
            case 3:
                printf("Enter the name of file: ");
                scanf("%s", f);
                
                for (i = 0; i < dir.fcnt; i++){
                    if(strcmp(f, dir.fname[i]) == 0){
                        printf("File is found!\n");
                        break;                    
                    }
                }
                
                if(i == dir.fcnt){
                    printf("File not found!\n");
                }
                break;
             
            case 4:
                if(dir.fcnt == 0){
                    printf("Direcotry is empty\n");
                }else{
                    printf("The files are: ");
                    
                    for (i = 0; i < dir.fcnt; i++){
                        printf("\n%s", dir.fname[i]);
                    }
                    printf("\n");
                }
                break;
                
            case 5:
                printf("Bye!\n");
                exit(0);
                break;
                
            default:
                printf("Enter a valid input!");
                break;
        }
    }
}
