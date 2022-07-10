#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;

    do {
        h = get_int("Height:");
    } while (h <= 0 || h > 8);

    for (int k = 0; k < h; k++) {
        for (int j = 0; j < h - k - 1; j ++) {
            printf(" ");
        }
        for (int j = 0; j <= k; j ++) {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j <= k; j ++) {
            printf("#");
        }
        printf("\n");
    }
}
