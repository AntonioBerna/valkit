#include <stdlib.h>

int main(void) {
    int *arr = malloc(5 * sizeof(*arr));
    arr[10] = 42; // Buffer overflow
    free(arr);
    return 0;
}