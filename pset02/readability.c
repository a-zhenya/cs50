#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int main() {
    string text = get_string("Text: ");
    int w, l, s; // words, letters, sentences
    w = l = s = 0;
    while (*text) {
        if ( isalpha(*text) ) {
            w ++;
            while ( isalpha(*text) || *text == '\'' || *text == '-' ) {
                if ( isalpha(*text) ) {
                    l ++;
                }
                text ++;
            }
        } else if ( *text == '.' || *text == '!' || *text == '?' ) {
            s ++;
            text ++;
        } else {
            text ++;
        }
    }
    if ( s == 0 ) {
        s = 1;
    }
    double L = (double)l*100.0 / (double) w;
    double S = (double)s*100.0 / (double) w;
    double score = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int)(score + 0.5);
    if (grade >= 16) {
        printf("Grade 16+\n");
    } else if ( grade < 1 ) {
        printf("Before Grade 1\n");
    } else {
        printf("Grade %i\n", grade);
    }
    return 0;
}