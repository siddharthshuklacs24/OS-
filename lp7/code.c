#include <stdio.h>

#define MAX 50

// Function to print frame contents
void printFrames(int frames[], int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

// FIFO Algorithm
void FIFO(int pages[], int n, int f) {
    int frames[MAX];
    int pageFaults = 0;
    int index = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("FIFO Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % f;

            pageFaults++;

            printf("PF No. %d: ", pageFaults);
            printFrames(frames, f);
        }
    }

    printf("FIFO Page Faults: %d\n", pageFaults);
}

// LRU Algorithm
void LRU(int pages[], int n, int f) {
    int frames[MAX], time[MAX];
    int pageFaults = 0;
    int counter = 0;

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = 0;

            for (int j = 1; j < f; j++) {
                if (time[j] < time[pos])
                    pos = j;
            }

            frames[pos] = pages[i];

            counter++;
            time[pos] = counter;

            pageFaults++;

            printf("PF No. %d: ", pageFaults);
            printFrames(frames, f);
        }
    }

    printf("LRU Page Faults: %d\n", pageFaults);
}

// Function for Optimal Algorithm
int predict(int pages[], int frames[], int n, int index, int f) {
    int farthest = index;
    int pos = -1;

    for (int i = 0; i < f; i++) {
        int j;

        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }

        if (j == n)
            return i;
    }

    if (pos == -1)
        return 0;
    else
        return pos;
}

// Optimal Algorithm
void Optimal(int pages[], int n, int f) {
    int frames[MAX];
    int pageFaults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement Process:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int empty = -1;

            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1) {
                frames[empty] = pages[i];
            } else {
                int pos = predict(pages, frames, n, i + 1, f);
                frames[pos] = pages[i];
            }

            pageFaults++;

            printf("PF No. %d: ", pageFaults);
            printFrames(frames, f);
        }
    }

    printf("Optimal Page Faults: %d\n", pageFaults);
}

int main() {
    int f, n;
    int pages[MAX];

    printf("Enter the number of Frames: ");
    scanf("%d", &f);

    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    FIFO(pages, n, f);

    LRU(pages, n, f);

    Optimal(pages, n, f);

    return 0;
}
