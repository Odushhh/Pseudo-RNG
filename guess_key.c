#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/evp.h>
//#include <openssl/aes.h>
#include <openssl/rand.h>

#define KEYSIZE 16

// Function to convert hex to binary and print
void print_hex_as_binary(const char *hex, size_t length) {
    for (size_t i = 0; i < length; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (hex[i] >> j) & 1); // Extract and print each bit
        }
        printf(" "); // Add space between bytes for readability
    }
    printf("\n");
}

void generate_key(char *key, int seed) {
    srand(seed);
    for (int i = 0; i < KEYSIZE; i++) {
        key[i] = rand() % 256;
    }
}

int main() {
    char key[KEYSIZE];
    unsigned char known_plaintext[] = {0x25, 0x50, 0x44, 0x46, 0x2d, 0x31, 0x2e, 0x35, 0x0a, 0x25, 0xd0, 0xd4, 0xc5, 0xd8, 0x0a, 0x34};
    unsigned char known_ciphertext[] = {0xd0, 0x6b, 0xf9, 0xd0, 0xda, 0xbb, 0xe8, 0xef, 0x88, 0x06, 0x60, 0xd2, 0xaf, 0x65, 0xaa, 0x82};
    char iv[] = {0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0xA2, 0xB2, 0xC2, 0xD2, 0xE2, 0xF2};
    char decrypted[KEYSIZE];

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Failed to create cipher context\n");
        return 1;
    }

    // Convert and print known_plaintext and known_ciphertext in binary
    printf("Known Plaintext in Binary:\n");
    print_hex_as_binary(known_plaintext, KEYSIZE);

    printf("Known Ciphertext in Binary:\n");
    print_hex_as_binary(known_ciphertext, KEYSIZE);

    /*
    char known_plaintext[] = "255044462d312e350a25d0d4c5d80a34";
    char known_ciphertext[] = "d06bf9d0dabbe8ef880660d2af65aa82";
    char iv[] = "09080706050403020100A2B2C2D2E2F2";

    // Convert known_plaintext and known_ciphertext to binary
    // ... (code to convert hex to binary)

    // Iterate through possible seeds
    for (int seed = 1523999329; seed <= 1524006529; seed++) {
        generate_key(key, seed);
        // Compare generated key with known ciphertext
        // ... (code to compare and decrypt)
    }
    */


    for (int seed = 1523999329; seed <= 1524006529; seed++) {
        generate_key(key, seed);

        // Initialize decryption context
        if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, (unsigned char *)key, (unsigned char *)iv)) {
            fprintf(stderr, "Decryption initialization failed\n");
            EVP_CIPHER_CTX_free(ctx);
            return 1;
        }

        int len, decrypted_len;

        // Perform decryption
        if (!EVP_DecryptUpdate(ctx, (unsigned char *)decrypted, &len, (unsigned char *)known_ciphertext, KEYSIZE)) {
            fprintf(stderr, "Decryption failed\n");
            EVP_CIPHER_CTX_free(ctx);
            return 1;
        }
        decrypted_len = len;

        // Finalize decryption
        if (!EVP_DecryptFinal_ex(ctx, (unsigned char *)decrypted + len, &len)) {
            continue; // Skip seeds that fail decryption
        }
        decrypted_len += len;
    /*
        // Decrypt the known ciphertext with the generated key and IV
        AES_KEY aes_key;
        AES_set_decrypt_key(key, 128, &aes_key);
        char decrypted[KEYSIZE];
        AES_cbc_encrypt(known_ciphertext, decrypted, KEYSIZE, &aes_key, iv, AES_DECRYPT);
     */
        // Compare decrypted text with known plaintext
        if (memcmp(decrypted, known_plaintext, KEYSIZE) == 0) {
            printf("Key found! Seed: %d\n", seed);
            for (int i = 0; i < KEYSIZE; i++) {
                printf("%.2x", (unsigned char)key[i]);
            }
            printf("\n");

            EVP_CIPHER_CTX_free(ctx);
            return 0;
        }
    }

    printf("Key not found within the specified window.\n");
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}
