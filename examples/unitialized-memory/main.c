#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *ptr = malloc(sizeof(*ptr));
    if (*ptr == 0) {
        printf("Valore zero\n");
    }
    free(ptr);
    return 0;
}