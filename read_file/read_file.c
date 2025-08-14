#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *file_ptr;
    char ch;
    file_ptr = fopen("test.txt", "r");
    if(file_ptr == NULL){
        printf("File cannot be opened!\n");
        return EXIT_FAILURE;
    }
    
    printf("Content of the file: \n");
    while((ch = fgetc(file_ptr)) != EOF){
        printf("%c", ch);
    }
    fclose(file_ptr);
    return 0;
}
