#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    char opcode[10], operand[10], label[10], code[10], mnemonic[3];
    int locctr, start, length;
    FILE *f1, *f2, *f3, *f4;

    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("symtab.txt", "w");
    f4 = fopen("intert.txt", "w");

    fscanf(f1, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(f4, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(f1, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(f4, "%d\t", locctr);

        if (strcmp(label, "") != 0) {
            fprintf(f3, "%s\t%d\n", label, locctr);
        }

        rewind(f2);

        fscanf(f2, "%s %s", code, mnemonic);

        while (!feof(f2)) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3;
                break;
            }
            fscanf(f2, "%s %s", code, mnemonic);
        }

        if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            locctr += 3 * atoi(operand);
        } else if (strcmp(opcode, "BYTE") == 0) {
            ++locctr;
		}
		else if (strcmp(opcode, "RESB") == 0) {
				     locctr += atoi(operand);
        }

        fprintf(f4, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(f1, "%s %s %s", label, opcode, operand);
    }

    fprintf(f4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    length = locctr - start;

    printf("Length of the code: %d\n", length);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    return 0;
}
