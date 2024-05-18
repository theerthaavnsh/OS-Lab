#include <stdio.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

int frames[MAX_FRAMES];
int pages[MAX_PAGES];
int num_frames, num_pages;

void fifo() {
    int page_faults = 0;
    int frame_index = 0;

    // Initialize frames to -1 (empty)
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in a frame
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // If page is not in any frame, replace the oldest page
        if (!found) {
            frames[frame_index] = page;
            frame_index = (frame_index + 1) % num_frames;
            page_faults++;
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

    printf("Total page faults using FIFO: %d\n", page_faults);
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

    // Simulate FIFO page replacement algorithm
    fifo();

    return 0;
}
