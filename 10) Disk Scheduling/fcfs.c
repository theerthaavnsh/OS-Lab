#include <stdio.h>
#include <stdlib.h>

void fcfs(int head, int req[], int n) {
    int total_movement = 0;
    printf("Sequence: %d ", head);

    for (int i = 0; i < n; i++) {
        printf("-> %d ", req[i]);
        total_movement += abs(head - req[i]);
        head = req[i];
    }

    printf("\nTotal head movement using FCFS: %d\n", total_movement);
}

int main() {
    int head, n;

    printf("Enter the current position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    fcfs(head, req, n);

    return 0;
}
