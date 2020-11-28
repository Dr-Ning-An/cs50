#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            int sepiaRed, sepiaGreen, sepiaBlue;
            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtRed = tempRed;
            image[i][width - 1 - j].rgbtGreen = tempGreen;
            image[i][width - 1 - j].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumRed[height][width];
    int sumGreen[height][width];
    int sumBlue[height][width];


    sumRed[0][0] = image[0][0].rgbtRed + image[0][1].rgbtRed + \
                   image[1][0].rgbtRed + image[1][1].rgbtRed;
    sumRed[height - 1][0] = image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed + \
                            image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed;
    sumRed[0][width - 1] = image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed + \
                           image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed;
    sumRed[height - 1][width - 1] = image[height - 1][width - 1].rgbtRed + image[height - 2][width - 1].rgbtRed + \
                                    image[height - 1][width - 2].rgbtRed + image[height - 2][width - 2].rgbtRed;
    sumGreen[0][0] = image[0][0].rgbtGreen + image[0][1].rgbtGreen + \
                     image[1][0].rgbtGreen + image[1][1].rgbtGreen;
    sumGreen[height - 1][0] = image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen + \
                              image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen;
    sumGreen[0][width - 1] = image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen + \
                             image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen;
    sumGreen[height - 1][width - 1] = image[height - 1][width - 1].rgbtGreen + image[height - 2][width - 1].rgbtGreen + \
                                      image[height - 1][width - 2].rgbtGreen + image[height - 2][width - 2].rgbtGreen;
    sumBlue[0][0] = image[0][0].rgbtBlue + image[0][1].rgbtBlue + \
                    image[1][0].rgbtBlue + image[1][1].rgbtBlue;
    sumBlue[height - 1][0] = image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue + \
                             image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue;
    sumBlue[0][width - 1] = image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue + \
                            image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue;
    sumBlue[height - 1][width - 1] = image[height - 1][width - 1].rgbtBlue + image[height - 2][width - 1].rgbtBlue + \
                                     image[height - 1][width - 2].rgbtBlue + image[height - 2][width - 2].rgbtBlue;

    for (int i = 1; i < height - 1; i++)
    {
        sumRed[i][0] = image[i - 1][0].rgbtRed + image[i][0].rgbtRed + image[i + 1][0].rgbtRed + \
                       image[i - 1][1].rgbtRed + image[i][1].rgbtRed + image[i + 1][1].rgbtRed;
        sumGreen[i][0] = image[i - 1][0].rgbtGreen + image[i][0].rgbtGreen + image[i + 1][0].rgbtGreen + \
                         image[i - 1][1].rgbtGreen + image[i][1].rgbtGreen + image[i + 1][1].rgbtGreen;
        sumBlue[i][0] = image[i - 1][0].rgbtBlue + image[i][0].rgbtBlue + image[i + 1][0].rgbtBlue + \
                        image[i - 1][1].rgbtBlue + image[i][1].rgbtBlue + image[i + 1][1].rgbtBlue;
        sumRed[i][width - 1] = image[i - 1][width - 1].rgbtRed + image[i][width - 1].rgbtRed + image[i + 1][width - 1].rgbtRed + \
                               image[i - 1][width - 2].rgbtRed + image[i][width - 2].rgbtRed + image[i + 1][width - 2].rgbtRed;
        sumGreen[i][width - 1] = image[i - 1][width - 1].rgbtGreen + image[i][width - 1].rgbtGreen + image[i + 1][width - 1].rgbtGreen + \
                                 image[i - 1][width - 2].rgbtGreen + image[i][width - 2].rgbtGreen + image[i + 1][width - 2].rgbtGreen;
        sumBlue[i][width - 1] = image[i - 1][width - 1].rgbtBlue + image[i][width - 1].rgbtBlue + image[i + 1][width - 1].rgbtBlue + \
                                image[i - 1][width - 2].rgbtBlue + image[i][width - 2].rgbtBlue + image[i + 1][width - 2].rgbtBlue;
    }
    for (int j = 1; j < width - 1; j++)
    {
        sumRed[0][j] = image[0][j - 1].rgbtRed + image[0][j].rgbtRed + image[0][j + 1].rgbtRed + \
                       image[1][j - 1].rgbtRed + image[1][j].rgbtRed + image[1][j + 1].rgbtRed;
        sumGreen[0][j] = image[0][j - 1].rgbtGreen + image[0][j].rgbtGreen + image[0][j + 1].rgbtGreen + \
                         image[1][j - 1].rgbtGreen + image[1][j].rgbtGreen + image[1][j + 1].rgbtGreen;
        sumBlue[0][j] = image[0][j - 1].rgbtBlue + image[0][j].rgbtBlue + image[0][j + 1].rgbtBlue + \
                        image[1][j - 1].rgbtBlue + image[1][j].rgbtBlue + image[1][j + 1].rgbtBlue;
        sumRed[height - 1][j] = image[height - 1][j - 1].rgbtRed + image[height - 1][j].rgbtRed + image[height - 1][j + 1].rgbtRed + \
                                image[height - 2][j - 1].rgbtRed + image[height - 2][j].rgbtRed + image[height - 2][j + 1].rgbtRed;
        sumGreen[height - 1][j] = image[height - 1][j - 1].rgbtGreen + image[height - 1][j].rgbtGreen + \
                                  image[height - 1][j + 1].rgbtGreen + \
                                  image[height - 2][j - 1].rgbtGreen + image[height - 2][j].rgbtGreen + image[height - 2][j + 1].rgbtGreen;
        sumBlue[height - 1][j] = image[height - 1][j - 1].rgbtBlue + image[height - 1][j].rgbtBlue + image[height - 1][j + 1].rgbtBlue + \
                                 image[height - 2][j - 1].rgbtBlue + image[height - 2][j].rgbtBlue + image[height - 2][j + 1].rgbtBlue;
    }
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            sumRed[i][j] = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + \
                           image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + \
                           image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
            sumGreen[i][j] = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + \
                             image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + \
                             image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
            sumBlue[i][j] = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + \
                            image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + \
                            image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
        }
    }
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtRed = round(sumRed[i][j] / 9.0);
            image[i][j].rgbtGreen = round(sumGreen[i][j] / 9.0);
            image[i][j].rgbtBlue = round(sumBlue[i][j] / 9.0);
        }
    }
    image[0][0].rgbtRed = round(sumRed[0][0] / 4.0);
    image[0][0].rgbtGreen = round(sumGreen[0][0] / 4.0);
    image[0][0].rgbtBlue = round(sumBlue[0][0] / 4.0);
    image[0][width - 1].rgbtRed = round(sumRed[0][width - 1] / 4.0);
    image[0][width - 1].rgbtGreen = round(sumGreen[0][width - 1] / 4.0);
    image[0][width - 1].rgbtBlue = round(sumBlue[0][width - 1] / 4.0);
    image[height - 1][0].rgbtRed = round(sumRed[height - 1][0] / 4.0);
    image[height - 1][0].rgbtGreen = round(sumGreen[height - 1][0] / 4.0);
    image[height - 1][0].rgbtBlue = round(sumBlue[height - 1][0] / 4.0);
    image[height - 1][width - 1].rgbtRed = round(sumRed[height - 1][width - 1] / 4.0);
    image[height - 1][width - 1].rgbtGreen = round(sumGreen[height - 1][width - 1] / 4.0);
    image[height - 1][width - 1].rgbtBlue = round(sumBlue[height - 1][width - 1] / 4.0);
    for (int i = 1; i < height - 1; i++)
    {
        image[i][0].rgbtRed = round(sumRed[i][0] / 6.0);
        image[i][0].rgbtGreen = round(sumGreen[i][0] / 6.0);
        image[i][0].rgbtBlue = round(sumBlue[i][0] / 6.0);
        image[i][width - 1].rgbtRed = round(sumRed[i][width - 1] / 6.0);
        image[i][width - 1].rgbtGreen = round(sumGreen[i][width - 1] / 6.0);
        image[i][width - 1].rgbtBlue = round(sumBlue[i][width - 1] / 6.0);
    }
    for (int j = 1; j < width - 1; j++)
    {
        image[0][j].rgbtRed = round(sumRed[0][j] / 6.0);
        image[0][j].rgbtGreen = round(sumGreen[0][j] / 6.0);
        image[0][j].rgbtBlue = round(sumBlue[0][j] / 6.0);
        image[height - 1][j].rgbtRed = round(sumRed[height - 1][j] / 6.0);
        image[height - 1][j].rgbtGreen = round(sumGreen[height - 1][j] / 6.0);
        image[height - 1][j].rgbtBlue = round(sumBlue[height - 1][j] / 6.0);
    }
    return;
}
