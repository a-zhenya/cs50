#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int k = 0; k < height; k ++) {
        for (int l = 0; l < width; l ++) {
            int s = (int)image[k][l].rgbtRed
                + (int)image[k][l].rgbtGreen
                + (int)image[k][l].rgbtBlue;
            if (s % 3 == 2) {
                s += 1;
            }
            s /= 3;
            image[k][l].rgbtRed   = (BYTE)s;
            image[k][l].rgbtGreen = (BYTE)s;
            image[k][l].rgbtBlue  = (BYTE)s;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int k = 0; k < height; k ++) {
        for (int l = 0; l < width/2; l ++) {
            RGBTRIPLE tmp = image[k][l];
            image[k][l] = image[k][width - 1 - l];
            image[k][width - 1 - l] = tmp;
        }
    }
    return;
}

// Blur image
void add_to_triple(int triple[], RGBTRIPLE rgb, int mult) {
    triple[0] += (int)rgb.rgbtRed * mult;
    triple[1] += (int)rgb.rgbtGreen * mult;
    triple[2] += (int)rgb.rgbtBlue * mult;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE save_up[width];
    RGBTRIPLE save_left;
    for (int k = 0; k < height; k ++) {
        for (int l = 0; l < width; l ++) {
            int sumRGB[3] = {0, 0, 0};
            int count = 0;
            if (k > 0) {
                if (l > 0) {
                    add_to_triple(sumRGB, save_up[l - 1], 1);
                    count ++;
                }
                add_to_triple(sumRGB, save_up[l], 1);
                count ++;
                if (l < width - 1) {
                    add_to_triple(sumRGB, save_up[l + 1], 1);
                    count ++;
                }
            }
            if (l > 0) {
                add_to_triple(sumRGB, save_left, 1);
                save_up[l - 1] = save_left;
                count ++;
            }
            add_to_triple(sumRGB, image[k][l], 1);
            save_left = image[k][l];
            count ++;
            if (l < width - 1) {
                add_to_triple(sumRGB, image[k][l + 1], 1);
                count ++;
            }
            if (k < height - 1) {
                if (l > 0) {
                    add_to_triple(sumRGB, image[k + 1][l - 1], 1);
                    count ++;
                }
                add_to_triple(sumRGB, image[k + 1][l], 1);
                count ++;
                if (l < width - 1) {
                    add_to_triple(sumRGB, image[k + 1][l + 1], 1);
                    count ++;
                }
            }
            for (int t = 0; t < 3; t ++) {
                if ( (sumRGB[t] % count) *2 >= count ) {
                	sumRGB[t] += count;
                }
            }

            image[k][l].rgbtRed   = (BYTE)(sumRGB[0] / count);
            image[k][l].rgbtGreen = (BYTE)(sumRGB[1] / count);
            image[k][l].rgbtBlue  = (BYTE)(sumRGB[2] / count);

        }
        save_up[width - 1] = save_left;
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE save_up[width];
    RGBTRIPLE save_left;
    for (int k = 0; k < height; k ++) {
        for (int l = 0; l < width; l ++) {
            int Gx[3] = {0, 0, 0};
            int Gy[3] = {0, 0, 0};
            if (k > 0) {
                if (l > 0) {
                    add_to_triple(Gx, save_up[l - 1], -1);
                    add_to_triple(Gy, save_up[l - 1], -1);
                }
                add_to_triple(Gy, save_up[l], -2);
                if (l < width - 1) {
                    add_to_triple(Gx, save_up[l + 1], 1);
                    add_to_triple(Gy, save_up[l + 1], -1);
                }
            }
            if (l > 0) {
                add_to_triple(Gx, save_left, -2);
                save_up[l - 1] = save_left;
            }
            save_left = image[k][l];
            if (l < width - 1) {
                add_to_triple(Gx, image[k][l + 1], 2);
            }
            if (k < height - 1) {
                if (l > 0) {
                    add_to_triple(Gx, image[k + 1][l - 1], -1);
                    add_to_triple(Gy, image[k + 1][l - 1], 1);
                }
                add_to_triple(Gy, image[k + 1][l], 2);
                if (l < width - 1) {
                    add_to_triple(Gx, image[k + 1][l + 1], 1);
                    add_to_triple(Gy, image[k + 1][l + 1], 1);
                }
            }
            for (int t = 0; t < 3; t ++) {
                Gx[t] = (int)( sqrt( (float)Gx[t] * Gx[t]
                    + (float)Gy[t] * Gy[t] ) + 0.5 );
                if ( Gx[t] > 255) {
                    Gx[t] = 255;
                }
            }

            image[k][l].rgbtRed   = (BYTE)(Gx[0]);
            image[k][l].rgbtGreen = (BYTE)(Gx[1]);
            image[k][l].rgbtBlue  = (BYTE)(Gx[2]);
        }
        save_up[width - 1] = save_left;
    }
    return;
}

BYTE float_to_color_component(float x) {
    if (x > 255.0) {
        return 255;
    } else {
        return (BYTE)(x + 0.5);
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int k = 0; k < height; k ++) {
        for (int l = 0; l < width; l ++) {
            sepiaRed = .393 * image[k][l].rgbtRed + .769 * image[k][l].rgbtGreen + .189 * image[k][l].rgbtBlue;
            sepiaGreen = .349 * image[k][l].rgbtRed + .686 * image[k][l].rgbtGreen + .168 * image[k][l].rgbtBlue;
            sepiaBlue = .272 * image[k][l].rgbtRed + .534 * image[k][l].rgbtGreen + .131 * image[k][l].rgbtBlue;
            if (sepiaRed > 255.0) {
            }
            image[k][l].rgbtRed   = float_to_color_component(sepiaRed);
            image[k][l].rgbtGreen = float_to_color_component(sepiaGreen);
            image[k][l].rgbtBlue  = float_to_color_component(sepiaBlue);
        }
    }
    return;
}
