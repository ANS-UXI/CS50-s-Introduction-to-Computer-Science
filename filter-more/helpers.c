#include "helpers.h"
#include <stdio.h>
#include <math.h>

void average_pixel(int i, int j, int height, int width);
int X[] = {0, 0, 0, 0};
int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x = image[i][j].rgbtRed;
            int y = image[i][j].rgbtGreen;
            int z = image[i][j].rgbtBlue;
            float avg = (x + y + z) / 3.0; // Averaging three values of Red, Green, Blue
            avg = round(avg);
            image[i][j].rgbtRed = (int) avg;
            image[i][j].rgbtGreen = (int) avg;
            image[i][j].rgbtBlue = (int) avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = width / 2;
    int r_width = width - 1;
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE x[1];
        for (int j = 0; j < mid; j++)
        {
            x[0] = image[i][j];
            image[i][j] = image[i][r_width - j];
            image[i][r_width - j] = x[0];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE backup[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average_pixel(i, j, height, width);
            int sum_r = 0, sum_g = 0, sum_b = 0;
            int count = 0;
            for (int k = X[0]; k <= X[1]; k++)
            {
                for (int l = X[2]; l <= X[3]; l++)
                {
                    sum_r = sum_r + (int) image[k][l].rgbtRed;
                    sum_g = sum_g + (int) image[k][l].rgbtGreen;
                    sum_b = sum_b + (int) image[k][l].rgbtBlue;
                    count++;
                }
            }
            backup[i][j].rgbtRed = round(sum_r / (float) count);
            backup[i][j].rgbtGreen = round(sum_g / (float) count);
            backup[i][j].rgbtBlue = round(sum_b / (float) count);
        }
    }
    for (int i = 0; i < height; i++) // Copying from backup to original image
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = backup[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int n_height = height + 2;
    int n_width = width + 2;
    RGBTRIPLE backup[n_height][n_width]; // Making another image which contains black pixel past the original image's edges
    RGBTRIPLE backup_1[height][width];

    for (int i = 0; i < n_height; i++)
    {
        for (int j = 0; j < n_width; j++)
        {
            if (i == 0 || i == n_height - 1) // Assigning the values 0
            {
                backup[i][j].rgbtRed = 0;
                backup[i][j].rgbtGreen = 0;
                backup[i][j].rgbtBlue = 0;
            }
            else if (j == 0 || j == n_width - 1) // Assigning the values 0
            {
                backup[i][j].rgbtRed = 0;
                backup[i][j].rgbtGreen = 0;
                backup[i][j].rgbtBlue = 0;
            }
            else
            {
                backup[i][j] = image[i - 1][j - 1]; // Assigning the original value of the image to the backup
            }
        }
    }

    for (int i = 1; i < n_height - 1; i++) // Iterating through the backup image
    {
        for (int j = 1; j < n_width - 1; j++)
        {
            average_pixel(i, j, n_height, n_width);
            int gx_red = 0, gy_red = 0, HforG = 0, WforG = 0, gx_green = 0, gy_green = 0, gx_blue = 0, gy_blue = 0;
            for (int k = X[0]; k <= X[1]; k++)
            {
                WforG = 0;
                for (int l = X[2]; l <= X[3]; l++)
                {
                    gx_red = gx_red + Gx[HforG][WforG] * (int) backup[k][l].rgbtRed;
                    gx_green = gx_green + Gx[HforG][WforG] * (int) backup[k][l].rgbtGreen;
                    gx_blue = gx_blue + Gx[HforG][WforG] * (int) backup[k][l].rgbtBlue;

                    gy_red = gy_red + Gx[WforG][HforG] * (int) backup[k][l].rgbtRed;
                    gy_green = gy_green + Gx[WforG][HforG] * (int) backup[k][l].rgbtGreen;
                    gy_blue = gy_blue + Gx[WforG][HforG] * (int) backup[k][l].rgbtBlue;

                    WforG++;
                }
                HforG++;
            }

            if (gx_red == 0 && gy_red == 0) // Checking whether there is no change in the value
            {
                backup_1[i - 1][j - 1].rgbtRed = backup[i][j].rgbtRed;
            }
            else
            {
                double pow_add = pow((double) gx_red, 2.0) + pow((double) gy_red, 2.0);
                backup_1[i - 1][j - 1].rgbtRed = round(sqrt(pow_add)) > 255 ? 255 : round(sqrt(pow_add));
            }

            if (gx_green == 0 && gy_green == 0) // Checking whether there is no change in the value
            {
                backup_1[i - 1][j - 1].rgbtGreen = backup[i][j].rgbtGreen;
            }
            else
            {
                double pow_add = pow((double) gx_green, 2.0) + pow((double) gy_green, 2.0);
                backup_1[i - 1][j - 1].rgbtGreen = round(sqrt(pow_add)) > 255 ? 255 : round(sqrt(pow_add));
            }

            if (gx_blue == 0 && gy_blue == 0) // Checking whether there is no change in the value
            {
                backup_1[i - 1][j - 1].rgbtBlue = backup[i][j].rgbtBlue;
            }
            else
            {
                double pow_add = pow((double) gx_blue, 2.0) + pow((double) gy_blue, 2.0);
                backup_1[i - 1][j - 1].rgbtBlue = round(sqrt(pow_add)) > 255 ? 255 : round(sqrt(pow_add));
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = backup_1[i][j];
        }
    }
}

// To generate the initial and final posn of the outer and inner loop, stored in X
void average_pixel(int i, int j, int height, int width)
{
    if (i == 0)
    {
        X[0] = i;
        X[1] = i + 1;
    }
    else
    {
        X[0] = i - 1;
        if (i == (height - 1))
        {
            X[1] = i;
        }
        else
        {
            X[1] = i + 1;
        }
    }

    if (j == 0)
    {
        X[2] = j;
        X[3] = j + 1;
    }
    else
    {
        X[2] = j - 1;
        if (j == (width - 1))
        {
            X[3] = j;
        }
        else
        {
            X[3] = j + 1;
        }
    }
}