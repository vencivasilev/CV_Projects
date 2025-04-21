#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototypes
bool is_valid_key(string key);
char substitute(char c, string key);

int main(int argc, string argv[])
{
    // Ensure the user provided exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    // Validate the key
    if (!is_valid_key(key))
    {
        printf("Key must be 26 characters long and contain each letter exactly once.\n");
        return 1;
    }

    // Get plaintext input from the user
    string plaintext = get_string("plaintext: ");

    // Encrypt the plaintext
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", substitute(plaintext[i], key));
    }
    printf("\n");

    return 0;
}

// Function to check if the key is valid
bool is_valid_key(string key)
{
    // Key must be 26 characters long
    if (strlen(key) != 26)
    {
        return false;
    }

    // Check for duplicates and ensure all characters are alphabetic
    bool seen[26] = {false};
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int index = tolower(key[i]) - 'a';
        if (seen[index])
        {
            return false;
        }
        seen[index] = true;
    }

    return true;
}

// Function to substitute a character based on the key
char substitute(char c, string key)
{
    if (isalpha(c))
    {
        bool is_upper = isupper(c);
        int index = tolower(c) - 'a';
        char substituted = key[index];
        return is_upper ? toupper(substituted) : tolower(substituted);
    }
    else
    {
        // Non-alphabetic characters remain unchanged
        return c;
    }
}
