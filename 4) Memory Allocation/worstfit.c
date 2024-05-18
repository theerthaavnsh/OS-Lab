#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int size;
    int allocated;
    struct Block *next;
} Block;

typedef struct Process {
    int size;
} Process;

void worstFit(Block *head, Process *processes, int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        Block *worstBlock = NULL, *current = head;
        while (current != NULL) {
            if (!current->allocated && current->size >= processes[i].size) {
                if (worstBlock == NULL || current->size > worstBlock->size) {
                    worstBlock = current;
                }
            }
            current = current->next;
        }
        if (worstBlock != NULL) {
            worstBlock->allocated = 1;
            printf("Process %d allocated to block of size %d\n", i + 1, worstBlock->size);
        } else {
            printf("Process %d cannot be allocated\n", i + 1);
        }
    }
}

int main() {
    int numBlocks, numProcesses;

    printf("Enter number of blocks: ");
    scanf("%d", &numBlocks);

    Block *head = NULL, *current = NULL;
    for (int i = 0; i < numBlocks; i++) {
        Block *newBlock = (Block *)malloc(sizeof(Block));
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &newBlock->size);
        newBlock->allocated = 0;
        newBlock->next = NULL;
        if (head == NULL) {
            head = newBlock;
        } else {
            current->next = newBlock;
        }
        current = newBlock;
    }

    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);

    Process processes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processes[i].size);
    }

    worstFit(head, processes, numProcesses);

    return 0;
}
