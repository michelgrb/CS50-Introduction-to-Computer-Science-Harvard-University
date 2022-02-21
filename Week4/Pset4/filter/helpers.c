#include "string.h"
#include "helpers.h"
#include "math.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int count = 0;
    //RGBTRIPLE buffer
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int r = image[h][w].rgbtRed;
            int g = image[h][w].rgbtGreen;
            int b = image[h][w].rgbtBlue;

            //set avrg and round it
            int avrg = round((r + g +  b) / 3.0);

            image[h][w].rgbtRed = avrg;
            image[h][w].rgbtGreen = avrg;
            image[h][w].rgbtBlue = avrg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //RGBTRIPLE buffer
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            //set starting values
            int r = image[h][w].rgbtRed;
            int g = image[h][w].rgbtGreen;
            int b = image[h][w].rgbtBlue;

            //for the red value
            int sr = round(.393 * r + .769 * g + .189 * b);
            if (sr > 255)
            {
                sr = 255;
            }

            //for the green value
            int sg = round(.349 * r + .686 * g + .168 * b);
            if (sg > 255)
            {
                sg = 255;
            }

            //for the blue value
            int sb = round(.272 * r + .534 * g + .131 * b);
            if (sb > 255)
            {
                sb = 255;
            }

            image[h][w].rgbtRed = sr;
            image[h][w].rgbtGreen = sg;
            image[h][w].rgbtBlue = sb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE px;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < (width / 2); w++)
        {
            px = image[h][w];

            //change values of equivalent pixel
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = px;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyimg[height][width];
    memcpy(copyimg, image, sizeof(RGBTRIPLE) * height * width);


    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            int ar = 0;
            int ag = 0;
            int ab = 0;

            float count = 0.0;

            //count all col around
            for (int hb = h - 1; hb < h + 2; hb++)
            {
                if (hb >= 0 && hb < height)
                {
                    for (int wb = w - 1; wb < w + 2; wb++)
                    {
                        if (wb >= 0 && wb < width)
                        {
                            //count colours
                            ar = ar + copyimg[hb][wb].rgbtRed;
                            ag = ag + copyimg[hb][wb].rgbtGreen;
                            ab = ab + copyimg[hb][wb].rgbtBlue;
                            count++;

                        }
                    }
                }
            }

            //dev by count of pixels around norm: 9
            ar = round(ar / count * 1.0);
            ag = round(ag / count * 1.0);
            ab = round(ab / count * 1.0);

            // apply values to pixel in mid
            image[h][w].rgbtRed = ar;
            image[h][w].rgbtGreen = ag;
            image[h][w].rgbtBlue = ab;

        }
    }
    return;
}
