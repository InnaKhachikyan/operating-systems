#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

proc *processes;
int proc_count;

static void mark_arrived(int current_time, proc *arr, MinHeap *h) {
	for(int i = 0; i < proc_count; i++) {
		if(arr[i].arrival_time <= current_time && arr[i].in_heap == 0) {
			arr[i].in_heap = 1;
			heap_insert(h, &arr[i]);
		}
	}
}

static proc* search_min_arrival(proc *arr, int n) {
	int min_idx = -1;
	for(int i = 0; i < n; i++) {
		if(arr[i].in_heap == 0) {
			if(min_idx == -1 || arr[i].arrival_time < arr[min_idx].arrival_time) {
				min_idx = i;
			}
			else if(arr[i].arrival_time == arr[min_idx].arrival_time) {
				if(arr[i].burst_time < arr[min_idx].burst_time) {
					min_idx = i;
				}
			}
		}
	}
	return (min_idx == -1) ? NULL : &arr[min_idx];
}

void sjf_scheduler(proc *arr) {
	MinHeap *heap = create_heap(proc_count);
	int current_time = 0;
	int to_do = proc_count;
	while(to_do > 0) {
		mark_arrived(current_time, arr, heap);
		proc *next;
		if(heap->size == 0) {
			next = search_min_arrival(arr, proc_count);
			current_time = next->arrival_time;
		}
		else {
			next = extract_min(heap);
		}
		printf("Executing proc with pid: %d, arrival time: %d, burst time: %d\n", next->pid, next->arrival_time, next->burst_time);
		next->waiting_time = current_time - next->arrival_time;
		next->response_time = next->waiting_time;
		next->turnaround_time = next->waiting_time + next->burst_time;
		next->in_heap = 2;
		current_time += next->burst_time;
		to_do--;
	}
	free_heap(heap);
}

void print_gantt_chart(proc *arr) {
        int wait_total = 0;
        int response_total = 0;
        int tat_total = 0;
        printf(" === SJF Gantt chart === \n");
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
                new_proc.pid = i;
                printf("Enter the arrival time and burst time for process %d: ", i+1);
                if( (scanf("%d %d", &(new_proc.arrival_time), &(new_proc.burst_time))) != 2) { 
                        printf("Scan failed\n"); 
                        exit(1); 
                }
                new_proc.in_heap = 0;
                processes[i] = new_proc;
        }
}

int main(void) {
        
	create_processes();

        sjf_scheduler(processes);

	print_gantt_chart(processes);

        free(processes);
        processes = NULL;
}

