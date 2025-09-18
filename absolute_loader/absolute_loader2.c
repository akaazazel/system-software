#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fP;
    int i, addr1, j, staddr1;
    char name[10], line[100], name1[10], addr[10], ch, staddr[10];

    printf("Enter your program name: ");
    scanf("%s", name);

    fP = fopen("object_code.txt", "r");
    if (fP == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(fP, "%s", line); // Read header record

    // Fix: Use correct loop condition
    for (i = 2, j = 0; i < 8 && j < 6; i++, j++) {
        name1[j] = line[i];
    }
    name1[j] = '\0';
    printf("Name from object code %s \n", name1);

    if (strcmp(name, name1) == 0) {
        // Start reading records
        while (fscanf(fP, "%s", line) != EOF) {
            if (line[0] == 'T') {
                // Fix: Correct loop condition for extracting address
                for (i = 2, j = 0; i < 8 && j < 6; i++, j++) {
                    staddr[j] = line[i];
                }
                staddr[j] = '\0';
                staddr1 = (int)strtol(staddr, NULL, 16); // Convert hex string to int
                i = 9; // Start of object code after length

                while (line[i] != '$' && line[i] != '\0') {
                    if (line[i] != '^') {
                        printf("%04X\t%c%c\n", staddr1, line[i], line[i + 1]);
                        staddr1++;
                        i += 2;
                    } else {
                        i++;
                    }
                }
            } else if (line[0] == 'E') {
                printf("Jump to execution address %s\n", &line[2]);
            }
        }
    } else {
        printf("Program name does not match header.\n");
    }

    fclose(fP);
    return 0;
}

