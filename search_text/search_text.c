#include <stdio.h>
#include <string.h>
int main(){
    FILE *fp;
    char word[50], ch;
    char *filename = "test.txt";
    char *search = "the";
    int pos[10], loop;
    int count = 0, pointer = 0;
    
    fp = fopen(filename, "r");
    
    do{
        ch = fscanf(fp, "%s", word);
        if(strcmp(word, search) == 0){
            pos[count] = pointer;
            count++;
        }
        pointer++;
    }while(ch != EOF);
    
    if(count == 0){
        printf("'%s' is not found in %s\n", search, filename);
    }else{
        printf("'%s' is found at --> ", search);
        
        for (loop = 0; loop < count; loop++){
            printf("%d, ", pos[loop]);
        }
        printf("positions\n");
    }
    
    fclose(fp);
    return 0;
}

