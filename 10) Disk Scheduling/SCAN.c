#include <stdio.h>
#include <stdlib.h>

void scan(int head, int req[], int n, int max_track) {
    int total_movement = 0;
    int direction = 1; // 1 for right, -1 for left

    // Find the direction of movement
    if (head > max_track / 2) {
        direction = -1;
    }

    printf("Sequence: %d ", head);

    // Sort requests based on their distance from the head
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (abs(head - req[j]) > abs(head - req[j + 1])) {
                int temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    // Iterate over requests based on direction
    int i = 0;
    if (direction == 1) {
        while (i < n && req[i] < head) {
            i++;
        }
    } else {
        while (i < n && req[i] > head) {
            i++;
        }
    }

    while (i < n && i >= 0) {
        printf("-> %d ", req[i]);
        total_movement += abs(head - req[i]);
        head = req[i];
        i += direction;
    }

    // Go to the end of the disk
    if (direction == 1) {
        printf("-> %d ", max_track);
        total_movement += abs(head - max_track);
    } else {
        printf("-> 0 ");
        total_movement += abs(head - 0);
    }

    printf("\nTotal head movement using SCAN: %d\n", total_movement);
}

int main() {
    int head, n, max_track;

    printf("Enter the current position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the maximum track of the disk: ");
    scanf("%d", &max_track);

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    scan(head, req, n, max_track);

    return 0;
}
