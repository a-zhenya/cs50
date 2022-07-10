#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    string key = argv[1];
    if (strlen(key) != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    int count_symbols[26];
    for (int j = 0; j < 26; j++) {
        count_symbols[j] = 0;
    }
    for (int j = 0; j < 26; j++) {
        if (!isalpha(key[j])) {
            printf("Illegal character in key\n");
            return 1;
        }
        key[j] = toupper(key[j]);
        count_symbols[ key[j] - 'A' ]++;
        if (count_symbols[ key[j] - 'A' ] > 1) {
            printf("Duplicate symbol in key '%c' in position %i\n", key[j], j);
            return 1;
        }
    }
    string text = get_string("Plaintext: ");
    int len = strlen(text);
    for (char * s = text; *s; s++) {
        if (isalpha(*s)) {
            bool lower = islower(*s);
            if (lower) {
                *s = toupper(*s);
            }
            *s = key[ *s - 'A' ];
            if (lower) {
                *s = tolower(*s);
            }
        }
    }
    printf("ciphertext: %s\n", text);
    return 0;
}