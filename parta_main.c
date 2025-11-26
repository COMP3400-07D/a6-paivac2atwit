#include "parta.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argv < 2) {
        printf("Error: Missing arguements\n");
        return 1;
    }

    char* algo = argv[1];

    if (strcmp(algo, "fcfs") == 0) {
        if (argc < 3) {
            printf("Error: Missing arguements\n");
            return 1;
        }
    int plen = argc - 2;
    int* bursts = malloc(sizeof(int) * plen);
    for (int i = 0; i < plen; i++) {
        bursts[i] = atoi(argv[i + 2]);
    }

    struct pcb* procs = init_procs(bursts, plen);
    free(bursts);

    printf("Using FCFS\n\n");

    for (int i = 0; i < plen; i ++){
        printf("Accepted P%d: Burst %d\n", procs[i].pid, procs[i].burst_left);

    }

    int total_time = fcfs_run(procs, plen);

    int sum_wait = 0;
    for (int i = 0; i < plen; i++) {
        sum_wait += procs[i].wait;
    }

    double avg_wait = (double)sum_wait / plen;

    printf("Average wait time: %2f\n", avg_wait);

    free(procs);
    return 0;
    }
    else if (strcmp(algo, "rr") == 0) {
        if (argc < 4) {
            printf("Error: Missing arguemtns\n");
            return 1;
        }
        int quantum = atoi(argv[2]);
        int plen = argc - 3;
        int* bursts = malloc(sizeof(int) * plen);
        for (int i =0; i < plen; i++) {
            bursts[i] = atoi(argv[i + 3]);
        }

        struct pcb* procs = init_procs(bursts, plen);
        free(bursts);

        printf("Using RR(%d)\n\n", quantum);

        for (int i = 0; i < plen; i++) {
            printf("Accepted P%d: Burst %d\n", procs[i].pid, procs[i].burst_left);
        }

        int total_time = rr_run(procs, plen, quantum);

        int sum_wait = 0;
        for (int i =0; i < plen; i++) {
            sum_wait += procs[i].wait;
        }

        double avg_wait = (double)sum_wait / plen;

        printf("Average wait time: %.2f\n", avg_wait);

        free(procs);
        return 0;
    }
    
    else {
        printf("Error: Missing arguements\n");
        return 1;
    }
}
