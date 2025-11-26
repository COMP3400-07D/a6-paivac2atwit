#include "parta.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Takes an array of CPU bursts, and returns an array of PCBs.
 */
 struct pcb* init_procs(int* bursts, int blen) {
    struct pcb* procs = malloc(sizeof(struct pcb) * blen);
    if(procs == NULL) 
        return NULL;
    
    for (int i = 0; i < blen; i++) {
        procs[i].pid = i;
        procs[i].burst_left = bursts[i];
        procs[i].wait = 0;
    }
return procs;
}
/*
 * Prints the current values of each PCB.
 */
void printall(struct pcb* procs, int plen) {
printf("Current process states:\n");
    for (int i = 0; i < plen; i++) {
        printf("PID %d: burst_left=%d, wait=%d\n",
               procs[i].pid,
               procs[i].burst_left,
               procs[i].wait);
    }
    printf("\n");
}

/**
 * Reduces the selected process’s burst_left by amount, and increases the wait time of every other process by the same amount.
 */
void run_proc(struct pcb* procs, int plen, int current, int amount) {
    if (procs[current].burst_left > 0) {
        procs[current].burst_left -= amount;
        if (procs[current].burst_left < 0) {
            procs[current].burst_left = 0;
        }
    }
    procs[current].wait =0;
    for (int i = 0; i < plen; i++) {
        if (i == current) continue;
        if (procs[i].burst_left > 0) {
            procs[i].wait += amount;
        }
    }
}

/**
 * Simulates a First-Come, First-Served (FCFS) CPU scheduling algorithm over an array of PCBs.
 */
int fcfs_run(struct pcb* procs, int plen) {
    int total_time = 0;

    for (int i = 0; i < plen; i++) {
        procs[i].wait = total_time;
        total_time =+ procs[i].burst_left;
        procs[i].burst_left = 0;
    }
    return total_time;
}

/**
 * Determines the next runnable process in the Round Robin queue.
 */
int rr_next(int current, struct pcb* procs, int plen) {
    int all_done = 1;
    for (int i = 0; i < plen; i++) {
        if (procs[i].burst_left > 0) {
            all_done = 0;
            break;
        }
    }
    if (all_done) {
    return -1;
    } 

    int next = (current + 1) % plen;

    for (int i = 0; i < plen; i++) {
        int idx = (next + i) % plen;
        if (procs[idx].burst_left > 0) {
            return idx;
        }
    }

    return -1;
}
/**
 * Runs all processes using Round Robin scheduling with the given time quantum and returns the total execution time.
 */
int rr_run(struct pcb* procs, int plen, int quantum) {
    int total_time = 0;
    int current = 0;

    while (1) {
        current = rr_next(current, procs, plen);
        if (current == -1) 
            break;

        int run_time = (procs[current].burst_left < quantum) ? procs[current].burst_left : quantum;
        
        run_proc(procs, plen, current, run_time);
        total_time += run_time;
    }
    return total_time;
}

