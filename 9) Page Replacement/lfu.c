#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

int frames[MAX_FRAMES];
int pages[MAX_PAGES];
int num_frames, num_pages;

int find_index(int arr[], int n, int val) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == val)
            return i;
    }
    return -1;
}

void lfu() {
    int page_faults = 0;
    int frequency[MAX_FRAMES] = {0};

    // Initialize frames to -1 (empty)
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int frame_index = find_index(frames, num_frames, page);

        // If page is not in any frame, find the least frequently used frame
        if (frame_index == -1) {
            int min_frequency = INT_MAX;
            int min_index = 0;
            for (int j = 0; j < num_frames; j++) {
                if (frequency[j] < min_frequency) {
                    min_frequency = frequency[j];
                    min_index = j;
                }
            }
            frame_index = min_index;
            frames[frame_index] = page;
            frequency[frame_index] = 1;
            page_faults++;
        } else {
            frequency[frame_index]++;
        }

        // Print current frames
        printf("Frames: ");
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == -1) {
                printf("- ");
            } else {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("Total page faults using LFU: %d\n", page_faults);
}

int main() {
    // Get user input for number of frames and pages
    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);
    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    // Get user input for page references
    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    // Simulate LFU page replacement algorithm
    lfu();

    return 0;
}

