#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void merge(int arr[], int left, int middle, int right)
{
    // right, left, origin indexes
    int ri, li, oi;

    int size_of_leftmost = middle - left + 1;

    int size_of_rightmost = right - middle;

    // Temp merge containers
    int L[size_of_leftmost], R[size_of_rightmost];

    // Fill temp containers
    for (li = 0; li < size_of_leftmost; li++)
        L[li] = arr[left + li];

    for (ri = 0; ri < size_of_rightmost; ri++)
        R[ri] = arr[middle + 1 + ri]; 

    // Indexes reset
    ri = li = 0;
    oi = left;

    while (li < size_of_leftmost && ri < size_of_rightmost)
    {
        if (L[li] <= R[ri])
        {
            arr[oi] = L[li];

            li++;
        }
        else
        {
            arr[oi] = R[ri];

            ri++;
        }

        oi++;
    }

    // Merge remaining elements in left
    while (li < size_of_leftmost)
    {
        arr[oi] = L[li];
        li++;
        oi++;
    }

    // Merge remaining elements in right
    while (ri < size_of_leftmost)
    {
        arr[oi] = R[ri];
        ri++;
        oi++;
    }
}

/**
 * 
 * 
 */
void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        merge_sort(arr, left, middle);

        merge_sort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

void bubble_sort(int arr[], int size)
{
    bool swapped = true;

    while (swapped)
    {
        swapped = false;

        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;

                swapped = true;
            }
        }
    }
}

int main()
{
    int len = 10000;
    int bubble_arr[len];
    int merge_arr[len];

    int array_size = sizeof(bubble_arr) / sizeof(int);

    for (size_t i = 0; i < len; i++)
    {
        bubble_arr[i] = rand();
        merge_arr[i] = rand();
    }

    // Calculate the time taken by merge()
    clock_t tm, tb;

    tm = clock();

    merge_sort(bubble_arr, 0, array_size - 1);

    tm = clock() - tm;

    double time_taken_merge = ((double)tm) / CLOCKS_PER_SEC; // in seconds

    tb = clock();

    bubble_sort(merge_arr, array_size);

    tb = clock() - tb;

    double time_taken_bubble = ((double)tb) / CLOCKS_PER_SEC; // in seconds

    printf("Merge sort time take: %f ms\n", time_taken_merge);

    printf("Bubble time take: %f ms\n", time_taken_bubble);

    return 0;
}
