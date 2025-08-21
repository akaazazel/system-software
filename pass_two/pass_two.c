#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char opcode[20], operand[20], symbol[20], label[20];
    char code[20], mnemonic[25], character, add[20], object_code[50]; 

    int flag, flag1, locctr, location, loc;
    FILE *fp1, *fp2, *fp3, *fp4;
    
    fp1 = fopen("out.txt", "r");
    fp2 = fopen("twout.txt", "w");
    fp3 = fopen("opcode.txt", "r");
    fp4 = fopen("symbol.txt", "r");

    if(!fp1 || !fp2 || !fp3 || !fp4){
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(fp1, "%s%s%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        fprintf(fp2, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%d%s%s%s", &locctr, label, opcode, operand);
    }
    
    while (strcmp(opcode, "END") != 0) {
        flag = 0;
        rewind(fp3);  // important: reset opcode file scan
        while (fscanf(fp3, "%s%s", code, mnemonic) == 2) {
            if (strcmp(code, "END") == 0) break;
            if ((strcmp(opcode, code) == 0) && (strcmp(mnemonic, "**") != 0)) {
                flag = 1;
                break;
            }
        }

        if (strcmp(opcode, "END") != 0) {
            locctr += 3;
        }

        object_code[0] = '\0';  // reset object code

        if (flag == 1) {
            flag1 = 0;
            rewind(fp4);

            while (fscanf(fp4, "%s%d", symbol, &loc) == 2) {
                if (strcmp(symbol, operand) == 0) {
                    flag1 = 1;
                    break;
                }
            }

            if (flag1 == 1) {
                sprintf(add, "%d", loc);
                strcpy(object_code, mnemonic);
                strcat(object_code, add);
            } else if (strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD") == 0) {
                if (operand[0] == 'C') {
                    // convert characters to ASCII values
                    int i;
                    char temp[10];
                    object_code[0] = '\0';
                    for (i = 2; operand[i] != '\'' && operand[i] != '\0'; i++) {
                        sprintf(temp, "%d", operand[i]);
                        strcat(object_code, temp);
                    }
                } else if (operand[0] == 'X') {
                    // assume hex constant after X'
                    strncpy(object_code, operand + 2, strlen(operand) - 3);
                    object_code[strlen(operand) - 3] = '\0';
                } else {
                    strcpy(object_code, operand);
                }
            } else {
                strcpy(object_code, "");
            }
        }

        fprintf(fp2, "%s\t%s\t%s\t%d\t%s\n", label, opcode, operand, locctr, object_code);
        fscanf(fp1, "%d%s%s%s", &locctr, label, opcode, operand);
    }

    fprintf(fp2, "%s\t%s\t%s\t%d\n", label, opcode, operand, locctr);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}
