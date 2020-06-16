#include <stdio.h>
#include <cs50.h>

int main(void) {
    long card = get_long("Card number: ");
    int s = 0;
    bool odd = true;
    int prefix = -1;
    int len = 0;
    while (card != 0) {
        if (card < 100 && prefix < 0) {
            prefix = (int)card;
        }
        if (odd) {
            s += card % 10;
        } else {
            int times2 = card % 10 * 2;
            s += times2 % 10 + times2 / 10;
        }
        card /= 10;
        len ++;
        odd = ! odd;
    }
    if (s % 10 == 0) {
        if (15 == len && (prefix == 34 || prefix == 37)) {
            printf("AMEX\n");
        } else if (16 == len && prefix >= 51 && prefix <= 55) {
            printf("MASTERCARD\n");
        } else if (prefix >= 40 && prefix <= 49 && (13 == len || 16 == len)) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }
}
