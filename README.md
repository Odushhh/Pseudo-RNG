# Pseudo-Random Number Generator

## Overview
This project implements a Pseudo-Random Number Generation technique for generating encryption keys. It involves key generation using both system entropy and standard libraries.

This program will iterate through a range of seeds and attempt to decrypt a known ciphertext using the generated keys. If the correct key is found, it will print the seed and the corresponding key.


[Find the Pseudo-Random Number Generation Lab here](https://seedsecuritylabs.org/Labs_20.04/Crypto/Crypto_Random_Number/) 

[Download SEED-Ubunut 24.04](https://seedsecuritylabs.org/labsetup.html)

## Components
Project structure:

pseudo-rng/
├── README.md
├── generate_256bit_key
├── generate_256bit_key.c
├── generate_key
├── generate_key.c
├── guess_key
├── guess_key.c
└── LICENSE

- `generate_256bit_key.c`: Generates a 256-bit key using `/dev/urandom` for high-quality randomness.
- `generate_key.c`: Generates a 128-bit key using the standard library's `rand()` function seeded with the current time.
- `guess_key.c`: Attempts to guess a key by iterating through possible seeds and decrypting known ciphertext using the generated keys.
- `guess_key`, `generate_256bit_key`, `generate_key` : Executable files



## Requirements
- A C compiler (e.g., `GCC`)
- OpenSSL library - for cryptographic functions
- SEED-Ubuntu 20.04 VM (or you can tweak your Ubuntu to have SEED's capabilities)


## Usage

### Part 1: Generating an Encryption Key

Create a file for generating a random key 
```nano generate_key.c```
> Check `generate_key.c` in the repo

Compile code:
```gcc generate_key.c -o generate_key```

Run executable file & examine output:
```./generate_key```

N|B:
- The function `rand()` will generate a constant sequence of random numbers, while `srand()` ensures there is a unique pattern every single time the code is executed.

> **rand()%256** keeps the generated number within the 0 to 255 range 


### Part 2: Guessing the Key

Create a another file for the guessing key function/program 
```nano guess_key.c```
> Check `guess_key.c`  in the repo

According to the PDF file, convert the timestamp given to seconds since the Unix Epoch
```date -d "2018-04-17 23:08:49" +%s```

Compile code:
```gcc guess_key.c -o guess_key```

Run executable file & examine output:
```./guess_key```

N|B:- Use the **EVP API** (for encryption/decryption and for the cipher) instead of  **AES_DECRYPT**



### Part 3: Getting random numbers from `/dev/random` and `/dev/urandom`

Generate the random numbers:
```cat /dev/random | hexdump```
```cat /dev/urandom | hexdump```

Monitor entropy:
```watch -n 0.1 cat /proc/sys/kernel/random/entropy_avail```

Place results in new file:
```head -c 1M /dev/random > output.bin```

Check output file's details:
```ent output.bin```


### Part 4: Generating a 256-bit Encryption Key

Create a file for generating a random key 
```nano generate_256bit_key.c```
> Check `generate_256bit_key.c` in the repo

Compile code & and run the executable file generated:
```gcc generate_256bit_key.c -o generate_256bit_key```
```./generate_256bit_key```


-------------------------- FIN --------------------------
