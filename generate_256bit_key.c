#include <stdio.h>
#include <stdlib.h>

#define LEN 32 // 256 bits

int main() {
    unsigned char *key = (unsigned char *) malloc(sizeof(unsigned char) * LEN);
    if (key == NULL) {
        perror("Unable to allocate memory");
        return 1; // Handle memory allocation failure
    }

    FILE* random = fopen("/dev/urandom", "r");
    if (random == NULL) {
        perror("Unable to open /dev/urandom");
        free(key); // Free allocated memory before exiting
        return 1; // Handle file open failure
    }

    fread(key, sizeof(unsigned char) * LEN, 1, random);
    fclose(random);

    // Print the key
    for (int i = 0; i < LEN; i++) {
        printf("%.2x", key[i]);
    }
    printf("\n");

    // Free the dynamically allocated memory
    free(key);
    return 0;
}

