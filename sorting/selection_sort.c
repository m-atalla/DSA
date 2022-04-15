#include <stdio.h>

#define MAX_LEN 6

void print_array(int * arr) {
    for (int i=0; i<= MAX_LEN; i++) 
        printf("%d\n", arr[i]);
}

int main() {
    int x[] = { 9, 8, 1, 22, 6, 7, 12 };

    int temp;

    for (int i = 0; i <= MAX_LEN; i++) {

        int min_i = i;

        // Find next min index
        for (int j = i; j <= MAX_LEN; j++) {
            if (x[min_i] > x[j]) {
                min_i = j;
            }
        }

        // no swap needed
        if (min_i == i) continue;

        // swap
        temp = x[i];
        x[i] = x[min_i];
        x[min_i] = temp;
    }

    print_array(x);

    return 0;
}
