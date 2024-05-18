// Implementation of LRU (Least Recently Used) Page Replacement Algorithm in C programming

#include <stdio.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100
#define NOT_FOUND -1

int frames[MAX_FRAMES];
int pages[MAX_PAGES];
int num_frames, num_pages;

// Function to find the index of the page in the frames
int find_page_index(int page) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return NOT_FOUND;
}

void lru() {
    int page_faults = 0;
    int frame_usage[MAX_FRAMES] = {0}; // Keeps track of the time since each frame was used

    // Initialize frames to -1 (empty)
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int frame_index = find_page_index(page);

        // If page is not in any frame, find the least recently used frame
        if (frame_index == NOT_FOUND) {
            int lru_frame = 0;
            for (int j = 1; j < num_frames; j++) {
                if (frame_usage[j] < frame_usage[lru_frame]) {
                    lru_frame = j;
                }
            }
            frame_index = lru_frame;
            frames[frame_index] = page;
            page_faults++;
        }

        // Update frame usage for all frames
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] != -1) {
                frame_usage[j]++;
            }
        }
        frame_usage[frame_index] = 0;

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

    printf("Total page faults using LRU: %d\n", page_faults);
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

    // Simulate LRU page replacement algorithm
    lru();

    return 0;
}
