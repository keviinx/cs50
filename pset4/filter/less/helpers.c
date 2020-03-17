#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) /* loop going thru the whole height*/
    {
        for (int j = 0; j < width; j++) /* loop going thru the width*/
        {
            RGBTRIPLE *pixel = &image[i][j]; /* make a pointer to the pixel*/
            unsigned int average = round((float)((pixel->rgbtRed + pixel->rgbtGreen + pixel->rgbtBlue)) / 3); /* calculate the average of RGB*/
            pixel->rgbtRed = average; /* set all the RBG to average value*/
            pixel->rgbtGreen = average;
            pixel->rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) /* loop going thru the whole height*/
    {
        for (int j = 0; j < width; j++) /* loop going thru the width*/
        {
            RGBTRIPLE *pixel = &image[i][j]; /* make a pointer to the pixel*/
            unsigned int sepia_red, sepia_green, sepia_blue; /* make variables to store sepia values*/

            sepia_red = round((float)((pixel->rgbtRed * 0.393) + (pixel->rgbtGreen * 0.769) + (pixel->rgbtBlue *
                                      0.189))); /*sepia formula for red*/
            if (sepia_red > 255) /*if result more than 255*/
            {
                sepia_red = 255; /*set to 255*/
            }
            sepia_green = round((float)((pixel->rgbtRed * 0.349) + (pixel->rgbtGreen * 0.686) + (pixel->rgbtBlue *
                                        0.168))); /*sepia formula for green*/
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            sepia_blue = round((float)((pixel->rgbtRed * 0.272) + (pixel->rgbtGreen * 0.534) + (pixel->rgbtBlue *
                                       0.131))); /*sepia formula for blue*/
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }
            pixel->rgbtRed = sepia_red; /* set all the RBG to sepia value*/
            pixel->rgbtGreen = sepia_green;
            pixel->rgbtBlue = sepia_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) /* loop going thru the whole height*/
    {
        for (int j = 0; j < width / 2; j++) /* loop going thru half the width*/
        {
            RGBTRIPLE *aPixel = &image[i][j], *bPixel = &image[i][(width - 1) - j]; /*create a variable for the pixels*/
            RGBTRIPLE temporary_pixel = image[i][j]; /*set the a pixel to temporary*/
            *aPixel = image[i][(width - 1) - j]; /*set the b pixel to a pixel*/
            *bPixel = temporary_pixel; /* set the temporary pixel to b pixel*/
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur_pixel[height][width]; /*make instance to hold blur array value*/

    for (int i = 0; i < height; i++) /*go thru whole height*/
    {
        for (int j = 0; j < width; j++) /* go thru whole width*/
        {
            unsigned int blur_red = 0, blur_green = 0, blur_blue = 0, pixel_count = 0;
            for (int a = i - 1; a < i + 2; a++)
            {
                for (int b = j - 1; b < j + 2; b++) /*go thru adjecent pixels*/
                {
                    if (a >= 0 && b >= 0 && a < height && b < width) /*check to not go out of border*/
                    {
                        blur_red += image[a][b].rgbtRed; /*get the rgb values*/
                        blur_green += image[a][b].rgbtGreen;
                        blur_blue += image[a][b].rgbtBlue;
                        pixel_count ++; /*increase counter*/
                    }
                }
            }
            blur_pixel[i][j].rgbtRed = round((float)blur_red / pixel_count); /*get the average value and store in the instance*/
            blur_pixel[i][j].rgbtGreen = round((float)blur_green / pixel_count);
            blur_pixel[i][j].rgbtBlue = round((float)blur_blue / pixel_count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) /* go thru all the pixel replacing the value with blur*/
        {
            RGBTRIPLE *pixel = &image[i][j]; /* point to the pixel address*/
            pixel->rgbtRed = blur_pixel[i][j].rgbtRed; /*replace with the blur values*/
            pixel->rgbtGreen = blur_pixel[i][j].rgbtGreen;
            pixel->rgbtBlue = blur_pixel[i][j].rgbtBlue;
        }
    }

    return;
}
