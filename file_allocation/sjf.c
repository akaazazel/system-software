#include <stdio.h>

int main(){
	int n, bt[10], wt[10], tat[10], i, j, temp;
	float avg_wt=0, avg_tat=0;
	
	printf("Enter the no of processes: ");
	scanf("%d", &n);
	printf("Enter the burst times: ");
	for (i = 0; i < n; i++){
		scanf("%d", &bt[i]);
	}
	
	for (i = 0; i < n-1; i++){
		for (j = 0; j < n-i-1; j++){
			if (bt[j] > bt[j+1]){
				temp = bt[j];
				bt[j] = bt[j+1];
				bt[j+1] = temp;
			}
		}
	}
	
	wt[0] = 0;
	for (i = 1; i < n; i++){
		wt[i] = wt[i-1] + bt[i-1];
	}
	
	for (i = 0; i < n; i++){
		tat[i] = wt[i] + bt[i];
		avg_wt += wt[i];
		avg_tat += tat[i];
	}
	
	printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
	for (i = 0; i < n; i++){
		printf("%d\t%d\t\t%d\t\t%d\n", i+1, bt[i], wt[i], tat[i]);
	}
	
	printf("Average waiting time: %.2f", avg_wt/n);
	printf("Average turnaround time: %.2f", avg_tat/n);
	
	return 0;
}
