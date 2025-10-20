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
			if(arr[j].arrival_time < arr[min_idx].arrival_time) {
				min_idx = j;
			}
		}
		swap(&arr[i], &arr[min_idx]);
	}
}

void fcfs_scheduler(proc *arr) {
	select_sort_proc_arrival_time(arr, proc_count);
	int current_time = 0;
	for(int i = 0; i < proc_count; i++) {
		printf("Executing proc with pid: %d, arrival time: %d, burst time: %d\n", arr[i].pid, arr[i].arrival_time, arr[i].burst_time);
		if(current_time < arr[i].arrival_time) {
			current_time = arr[i].arrival_time;
		}
		arr[i].waiting_time = current_time - arr[i].arrival_time;
		arr[i].response_time = arr[i].waiting_time;
		arr[i].turnaround_time = arr[i].waiting_time + arr[i].burst_time;
		current_time += arr[i].burst_time;
	}
}

void print_gantt_chart(proc *arr) {
	int wait_total = 0;
	int response_total = 0;
	int tat_total = 0;
	printf(" === FCFS Gantt chart === \n");
	printf("PID     AT     BT     WT     TAT     RT\n");
	for(int i = 0; i < proc_count; i++) {
		printf("%d       %d      %d      %d      %d       %d\n", arr[i].pid, arr[i].arrival_time, arr[i].burst_time, arr[i].waiting_time, arr[i].turnaround_time, arr[i].response_time);
		printf("\n");
		wait_total += arr[i].waiting_time;
		response_total += arr[i].response_time;
		tat_total += arr[i].turnaround_time;
	}

	double wait_average = (double)wait_total/(double)proc_count;
	double response_average = (double)response_total/(double)proc_count;
	double tat_average = (double)tat_total/(double)proc_count;

	printf("Average Waiting Time: %f\n", wait_average);
	printf("Average Response Time: %f\n", response_average);
	printf("Average Turnaround Time: %f\n", tat_average);
}

void create_processes() {
	 printf("Enter the number of processes: ");
        if(scanf("%d", &proc_count) != 1) {
                printf("scan failed\n");
                exit(1);
        }
        printf("\n");
        processes = (proc*)malloc(sizeof(proc)*proc_count);
        if(!processes) {
                perror("malloc");
                exit(1);
        }

        for(int i = 0; i < proc_count; i++) {
                proc new_proc;
                new_proc.pid = i+1;
                printf("Enter the arrival time and burst time for process %d: ", i+1);
                if( (scanf("%d %d", &(new_proc.arrival_time), &(new_proc.burst_time))) != 2) {
                        printf("Scan failed\n");
                        exit(1);
                }
                new_proc.turnaround_time = 0;
                new_proc.waiting_time = 0;
                new_proc.response_time = 0;
                processes[i] = new_proc;
        }
}

int main(void) {
	
	create_processes();

	fcfs_scheduler(processes);

	print_gantt_chart(processes);

	free(processes);
	processes = NULL;
}

