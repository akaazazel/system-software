#include <stdio.h>
#define MAX_BLOCKS 10

void allocate_file(int blocks[], int file_size){
	int start_block = -1;
	for (int i = 0; i <= MAX_BLOCKS - file_size; i++){
		int allocated = 0;
		for (int j = i; j < i + file_size; j++){
			if (blocks[j] == 1){
				allocated = 1;
				break;
			}
		}
		
		if (!allocated){
			start_block = i;
			break;
		}
	}
	
	if (start_block != -1){
		printf("File allocated from block %d to %d\n", start_block, start_block + file_size - 1);
		for (int i = start_block; i < start_block + file_size; i++){
			blocks[i] = 1;
		}
	}else{
		printf("Not enough contiguos space\n");
	}
}

int main(){
	int blocks[MAX_BLOCKS] = {0};
	int file_size;
	
	printf("Enter the file size (1-%d): ", MAX_BLOCKS);
	scanf("%d", &file_size);
	
	allocate_file(blocks, file_size);
	
	return 0;
}
