#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

int produce_item() {
    return rand() % 1000; // Generate a random item for simplicity
}

void consume_item(int item) {
    // Consume the item (in this case, just print it)
    printf("Consumed: %d\n", item);
}

void producer(int n) {
    int item;
    for (int i = 0; i < n; i++) {
        item = produce_item();
        printf("Produced: %d\n", item);
        while (((in + 1) % BUFFER_SIZE) == out) // Wait if buffer is full
            ;
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
    }
}

void consumer(int n) {
    int item;
    for (int i = 0; i < n; i++) {
        while (in == out) // Wait if buffer is empty
            ;
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        consume_item(item);
    }
}

int main() {
    int n_produce, n_consume;

    printf("Enter the number of items to produce: ");
    scanf("%d", &n_produce);
    printf("Enter the number of items to consume: ");
    scanf("%d", &n_consume);

    producer(n_produce);
    consumer(n_consume);

    return 0;
}
