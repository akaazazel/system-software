#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fptr1, *fptr2;
    char filename[100];
    int c;
    printf("Enter the file to open: ");
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if(fptr1 == NULL){
        printf("%s cannot be opened!\n", filename);
        exit(1);
    }
    
    printf("Enter the file to write: ");
    scanf("%s", filename);
    fptr2 = fopen(filename, "w");
    if(fptr2 == NULL){
        printf("%s cannot be opened!\n", filename);
        exit(1);
    }
    
    while((c = fgetc(fptr1)) != EOF){
        fputc(c, fptr2);
    }
    
    printf("File contents copied to %s.\n", filename);
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}
