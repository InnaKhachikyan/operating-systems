#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
	int turnaround_time;
	int waiting_time;
	int response_time;
} proc;

proc *processes;
int proc_count;

static void swap(proc *a, proc *b) {
	proc temp = *a;
	*a = *b;
	*b = temp;
}

static void select_sort_proc_arrival_time(proc *arr, int n) {
	for(int i = 0; i < n-1; i++) {
		int min_idx = i;
		for(int j = i + 1; j < n; j++) {
			if(processes[j].arrival_time < processes[min_idx].arrival_time) {
				min_idx = j;
			}
		}
		swap(&processes[i], &processes[min_idx]);
	}
}

void fcfs_scheduler(proc *arr) {
	select_sort_proc_arrival_time(arr, proc_count);
	//will simulate the running of the process, fork or toy-processes?
}

int main(void) {
	
	printf("Enter the number of processes: ");
	if(scanf("%d", &proc_count) != 1) {
		printf("scan failed\n");
		return 1;
	}
	printf("\n");
	processes = (proc*)malloc(sizeof(proc)*proc_count);
	if(!processes) {
		perror("malloc");
		return 1;
	}

	for(int i = 0; i < proc_count; i++) {
		proc new_proc;
		new_proc.pid = i;
		printf("Enter the arrival time and burst time for process %d: ", i+1);
		if( (scanf("%d %d", &(new_proc.arrival_time), &(new_proc.burst_time))) != 2) {
			printf("Scan failed\n");
			return 1;
		}
		processes[i] = new_proc;
	}

	fcfs_scheduler(processes);

	free(processes);
	processes = NULL;
}

