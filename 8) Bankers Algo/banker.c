#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int finish[MAX_PROCESSES];

int num_processes, num_resources;

void initialize() {
    // Initialize finish array to all zeros
    for (int i = 0; i < num_processes; i++) {
        finish[i] = 0;
    }
}

int is_safe() {
    int work[MAX_RESOURCES];
    int temp_finish[MAX_PROCESSES];

    // Initialize work and temp_finish arrays
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < num_processes; i++) {
        temp_finish[i] = finish[i];
    }

    // Find an unfinished process that can be satisfied with available resources
    int count = 0;
    while (count < num_processes) {
        int found = 0;
        for (int i = 0; i < num_processes; i++) {
            if (temp_finish[i] == 0) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == num_resources) {
                    // Process can be satisfied
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    temp_finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        // If no such process is found, system is in an unsafe state
        if (!found) {
            return 0;
        }
    }
    // If all processes can be satisfied, system is in a safe state
    return 1;
}

void request_resources(int process_num, int request[]) {
    // Check if request is within need
    for (int i = 0; i < num_resources; i++) {
        if (request[i] > need[process_num][i]) {
            printf("Error: Request exceeds maximum claim\n");
            return;
        }
    }

    // Check if request is within available resources
    for (int i = 0; i < num_resources; i++) {
        if (request[i] > available[i]) {
            printf("Error: Request exceeds available resources\n");
            return;
        }
    }

    // Simulate resource allocation
    for (int i = 0; i < num_resources; i++) {
        available[i] -= request[i];
        allocation[process_num][i] += request[i];
        need[process_num][i] -= request[i];
    }

    // Check if system is in safe state after allocation
    if (is_safe()) {
        printf("Request granted\n");
    } else {
        printf("Request denied, system in unsafe state\n");

        // Rollback resource allocation
        for (int i = 0; i < num_resources; i++) {
            available[i] += request[i];
            allocation[process_num][i] -= request[i];
            need[process_num][i] += request[i];
        }
    }
}

int main() {
    // Get user input for number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    // Get user input for available resources
    printf("Enter available resources: ");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    // Get user input for maximum resource allocation
    printf("Enter maximum resource allocation for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
    }

    initialize();

    // Get user input for resource request
    int process_num;
    printf("Enter process number requesting resources: ");
    scanf("%d", &process_num);
    printf("Enter resource request for process %d: ", process_num);
    int request[num_resources];
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &request[i]);
    }

    request_resources(process_num, request);

    return 0;
}
