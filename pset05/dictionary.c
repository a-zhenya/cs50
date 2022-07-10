// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool strcmpi(const char * a, const char * b) {
    while ( (*a) && (*b) && (tolower(*a) == tolower(*b))) {
        a++; b++;
    }
    if ( *a == *b ) {
        return true;
    } else {
        return false;
    }
}

bool check(const char *word)
{
    unsigned int hash_word = hash(word);
    for (node * pnode = table[hash_word]; pnode != NULL; pnode = pnode->next) {
        if (strcmpi( word, pnode->word ) ) {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int res = 0;
    while ( *word ) {
        res += (unsigned int)tolower(*word);
        res *= 113;
        res %= 10000007;
        word ++;
    }
    res %= N;
    return res;
}

// Loads dictionary into memory, returning true if successful else false
unsigned int loaded = 0;
bool load(const char *dictionary)
{
    FILE * dictfile = fopen(dictionary, "r");
    if (dictfile == NULL) {
        return false;
    }
    for (unsigned int j = 0; j < N; j ++) {
        table[j] = NULL;
    }
    char buf[LENGTH + 2];
    while ( fgets(buf, LENGTH + 2, dictfile) ) {
        int len = strlen(buf);
        if (buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }
        unsigned int hash_word = hash( buf );
        node * pnode;
        if ( table[hash_word] == NULL ) {
            table[hash_word] = malloc( sizeof(node) );
            pnode = table[hash_word];
        } else {
            pnode = table[hash_word];
            while ( pnode->next ) {
                pnode = pnode->next;
            }
            pnode->next = malloc( sizeof(node) );
            pnode = pnode->next;
        }
        if ( pnode == NULL) {
            // free memory?
            return false;
        }
        pnode->next = NULL;
        strcpy( pnode->word, buf );
        loaded += 1;
    }
    fclose(dictfile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return loaded;
}

// Unloads dictionary from memory, returning true if successful else false
void unload_branch(node * branch) {
    if (branch != NULL) {
        unload_branch( branch->next );
        free(branch);
    }
}

bool unload(void)
{
    for (unsigned int j = 0; j < N; j ++) {
        if (table[j] != NULL) {
            unload_branch( table[j] );
            table[j] = NULL;
        }
    }
    return true;
}



