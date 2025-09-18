#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void convert(const char hex[]);
char bit[100];  // large enough to hold all binary bits from bitmask

int main() {
    char label[10], start_addr[10], prog_len[10], input[10], bitmask[12], ch;
    int start, address, tlen, i, opcode, operand, actual_addr;
    FILE *fp1, *fp2;

    printf("Enter the actual starting address: ");
    scanf("%x", &start);

    fp1 = fopen("RLIN.txt", "r");
    if (!fp1) {
        printf("Error: cannot open input file.\n");
        return 1;
    }

    fp2 = fopen("RLOUT.txt", "w");
    if (!fp2) {
        printf("Error: cannot open output file.\n");
        fclose(fp1);
        return 1;
    }

    fscanf(fp1, "%s", input);  // Read 'H'

    if (strcmp(input, "H") == 0) {
        fscanf(fp1, "%s", label);
        fscanf(fp1, "%s", start_addr);
        fscanf(fp1, "%s", prog_len);
    }

    fprintf(fp2, "----------------------------------------\n");
    fprintf(fp2, "ADDRESS\t\tINSTRUCTION\n");
    fprintf(fp2, "----------------------------------------\n");

    while (fscanf(fp1, "%s", input) != EOF) {
        if (strcmp(input, "T") == 0) {
            fscanf(fp1, "%x", &address);      // Address in text record
            fscanf(fp1, "%x", &tlen);         // Length of object code in bytes
            fscanf(fp1, "%s", bitmask);       // Bitmask (in hex)

            convert(bitmask);  // Convert hex bitmask to binary string

            address += start;  // Relocate base address

            int num_instructions = tlen / 3;  // Each instruction = 3 bytes

            for (i = 0; i < num_instructions; i++) {
                fscanf(fp1, "%x", &opcode);
                fscanf(fp1, "%x", &operand);

                if (bit[i] == '1') {
                    actual_addr = operand + start;
                } else {
                    actual_addr = operand;
                }

                fprintf(fp2, "%06X\t\t%02X%03X\n", address, opcode, actual_addr);
                address += 3;
            }
        } else if (strcmp(input, "E") == 0) {
            break;
        }
    }

    fprintf(fp2, "----------------------------------------\n");
    fclose(fp1);
    fclose(fp2);

    printf("\nRelocated program output (RLOUT.txt):\n\n");
    fp2 = fopen("RLOUT.txt", "r");
    while ((ch = fgetc(fp2)) != EOF) {
        putchar(ch);
    }
    fclose(fp2);

    return 0;
}

void convert(const char hex[]) {
    bit[0] = '\0';
    for (int i = 0; hex[i] != '\0'; i++) {
        switch (hex[i]) {
            case '0': strcat(bit, "0000"); break;
            case '1': strcat(bit, "0001"); break;
            case '2': strcat(bit, "0010"); break;
            case '3': strcat(bit, "0011"); break;
            case '4': strcat(bit, "0100"); break;
            case '5': strcat(bit, "0101"); break;
            case '6': strcat(bit, "0110"); break;
            case '7': strcat(bit, "0111"); break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': case 'a': strcat(bit, "1010"); break;
            case 'B': case 'b': strcat(bit, "1011"); break;
            case 'C': case 'c': strcat(bit, "1100"); break;
            case 'D': case 'd': strcat(bit, "1101"); break;
            case 'E': case 'e': strcat(bit, "1110"); break;
            case 'F': case 'f': strcat(bit, "1111"); break;
            default: strcat(bit, "0000"); break; // Fallback
        }
    }
}

