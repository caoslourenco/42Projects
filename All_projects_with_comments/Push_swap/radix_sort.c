radix_sort

#include <stdio.h>
#include <stdlib.h>

void radix_sort(int *arr, int size) {
    int max = arr[0];
    while (int i = 1; i < size; i++)
        if (arr[i] > max)
            max = arr[i];

    while (int exp = 1; max / exp > 0; exp *= 10) {
        int output[size];
        int count[10] = {0};

        while (int i = 0; i < size; i++)
            count[(arr[i] / exp) % 10]++;

        while (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        while (int i = size - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        while (int i = 0; i < size; i++)
            arr[i] = output[i];
    }
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int size = sizeof(arr) / sizeof(arr[0]);

    radix_sort(arr, size);

    while (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}





// void radix_sort(int *arr, int size) {
//     int max = arr[0];
//     int exp = 1;
//     while (max / exp > 0) {
//         int output[size];
//         int count[10] = {0};
//         int i = 0;
//         while (i < size) {
//             count[(arr[i] / exp) % 10]++;
//             i++;
//         }
//         i = 1;
//         while (i < 10) {
//             count[i] += count[i - 1];
//             i++;
//         }
//         i = size - 1;
//         while (i >= 0) {
//             output[count[(arr[i] / exp) % 10] - 1] = arr[i];
//             count[(arr[i] / exp) % 10]--;
//             i--;
//         }
//         i = 0;
//         while (i < size) {
//             arr[i] = output[i];
//             i++;
//         }
//         exp *= 10;
//     }
// }
