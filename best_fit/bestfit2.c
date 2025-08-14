#include <stdio.h>
#define MAX 25

int main() {
    int frag[MAX], b[MAX], f[MAX], i, j, nb, nf, temp, lowest;
    static int bf[MAX], ff[MAX];
    
    printf("Enter the number of blocks: ");
    scanf("%d", &nb);
    
    printf("Enter the number of files: ");
    scanf("%d", &nf);
    
    printf("Enter the size of blocks:\n");
    for (i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &b[i]);
    }
    
    printf("Enter the size of files:\n");
    for (i = 0; i < nf; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &f[i]);
    }
    
    for (i = 0; i < nf; i++) {
        lowest = 10000;
        for (j = 0; j < nb; j++) {
            if (bf[j] != 1) {
                temp = b[j] - f[i];
                if (temp >= 0 && lowest > temp) {
                    ff[i] = j;
                    lowest = temp;
                }
            }
        }
        frag[i] = b[ff[i]] - f[i];
        bf[ff[i]] = 1;
    }
    
    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment");
    for (i = 0; i < nf; i++) {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",
               i + 1, f[i], ff[i] + 1, b[ff[i]], frag[i]);
    }
    printf("\n");

    return 0;
}

