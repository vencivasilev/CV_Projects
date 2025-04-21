#include <stdio.h>
#include <ctype.h>

void caesar_encrypt(char plaintext[], int key, char ciphertext[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ciphertext[i] = (ch - base + key) % 26 + base;
        } else {
            ciphertext[i] = ch;  // Keep non-alphabetic characters as is
        }
    }
}

void caesar_decrypt(char ciphertext[], int key, char plaintext[]) {
    caesar_encrypt(ciphertext, -key, plaintext);  // Decrypt by reversing the key
}

int main(){
    char plaintext[] = "Hello";
    int key = 1;
    char encrypted[100] = {0};
    char decrypted[100] = {0};

    // Encrypt the plaintext
    caesar_encrypt(plaintext, key, encrypted);
    printf("Encrypted: %s\n", encrypted);

    // Decrypt the ciphertext
}

