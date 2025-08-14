#include <stdio.h>
#define MAX 25
	
int main(){
	int frag[MAX], blocks[MAX], files[MAX], i, j, nBlocks, nFile, temp, lowest=10000;
	static int isAllocated[MAX], allocated_block[MAX];
	
	printf("Enter the number of blocks: ");
	scanf("%d", &nBlocks);
	
	printf("Enter the number of files: ");
	scanf("%d", &nFile);
	
	printf("Enter the size of blocks: \n");
	for (i = 0; i < nBlocks; i++){
		printf("Block %d: ", i+1);
		scanf("%d", &blocks[i]);
	}
	
	printf("Enter the size of the file: \n");
	for (i = 0; i < nFile; i++){
		printf("File %d: ", i+1);
		scanf("%d", &files[i]);
	}
	
	for (i = 0; i < nFile; i++){
		for (j = 0; j < nBlocks; j++){
			if (isAllocated[j] != 1){
				temp = blocks[j] - files[i];
				if (temp >= 0 && lowest > temp){
					allocated_block[i] = j;
					lowest = temp;
				}
			}
		}
		frag[i] = lowest;
		isAllocated[allocated_block[i]] = 1;
		lowest = 10000;
	}
	
	printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment");
	for (i = 0; i < nFile && allocated_block[i] != 0; i++){
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i+1, files[i], allocated_block[i]+1, blocks[allocated_block[i]], frag[i]);
	}
	printf("\n");
	
	return 0;
}
