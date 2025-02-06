#include <stdlib.h>

int main(void) {
    int *leak = malloc(100 * sizeof(*leak));
    // free(leak); // Commenting this line will cause a memory leak
    return 0;
}