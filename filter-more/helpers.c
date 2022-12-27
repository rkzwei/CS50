#include "helpers.h"
#include "math.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through rows
    for (int i = 0; i < height; i++)
    {
        // iterate through column
        for (int j = 0; j < width; j++)
        {
            // float em
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            // average em

            int avg = round((blue + green + red) / 3);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate each row
    for (int i = 0; i < height; i++)
    {
        // iterates only to the halfway point of width, while switching values for image
        for (int j = 0; j < width / 2; j++)
        {
            //defines temporary variable to store original pixel value
            RGBTRIPLE temp = image[i][j];
            //swaps row pixels using lenght of width minus current position as acquirer
            image[i][j] = image[i][width - (j + 1)];
            //restores swapped value with original value
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the image file to store values
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // iterate through image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // define variables for use in surroundings formula
            int blue, red, green;
            blue = red = green = 0;

            //counter for formula
            float count = 0.00;
            // loops through surrounding positions
            for (int posX = -1; posX < 2; posX++)
            {
                for (int posY = -1; posY < 2; posY++)
                {
                    // defines current position in image
                    int x = i + posX;
                    int y = j + posY;

                    // rule to declare if pixel is valid
                    if (x < 0 || x > (height - 1) || y < 0 || y > (width - 1))
                    {
                        continue;
                    }

                    // add value to total for formula
                    blue += image[x][y].rgbtBlue;
                    green += image[x][y].rgbtGreen;
                    red += image[x][y].rgbtRed;

                    count++;

                }
                // calculate avg of neighbors
                copy[i][j].rgbtBlue = round(blue / count);
                copy[i][j].rgbtGreen = round(green / count);
                copy[i][j].rgbtRed = round(red / count);
            }
        }
    }

    //carry changes over to original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the image file to store values
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // create kernel tables
    int gX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int xRed = 0;
            int xBlue = 0;
            int xGreen = 0;
            int yRed = 0;
            int yBlue = 0;
            int yGreen = 0;

            // loop for neighbors
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    // rule for invalids
                    if (i - 1 + x < 0 || i - 1 + x > height - 1 || j - 1 + y < 0 || j - 1 + y > width - 1)
                    {
                        continue;
                    }
                    // gX on each color
                    xRed = xRed + (image[i - 1 + x][j - 1 + y].rgbtRed * gX[x][y]);
                    xGreen = xGreen + (image[i - 1 + x][j - 1 + y].rgbtGreen * gX[x][y]);
                    xBlue = xBlue + (image[i - 1 + x][j - 1 + y].rgbtBlue * gX[x][y]);

                    // gY on each color
                    yRed = yRed + (image[i - 1 + x][j - 1 + y].rgbtRed * gY[x][y]);
                    yGreen = yGreen + (image[i - 1 + x][j - 1 + y].rgbtGreen * gY[x][y]);
                    yBlue = yBlue + (image[i - 1 + x][j - 1 + y].rgbtBlue * gY[x][y]);
                }
            }
            int red = round(sqrt((xRed * xRed) + (yRed * yRed)));
            int green = round(sqrt((xGreen * xGreen) + (yGreen * yGreen)));
            int blue = round(sqrt((xBlue * xBlue) + (yBlue * yBlue)));

            //cap at 255
            if (red > 255)
            {
                red = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            // loop to copy
            copy[i][j].rgbtRed = red;
            copy[i][j].rgbtGreen = green;
            copy[i][j].rgbtBlue = blue;
        }
    }

    // mv to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];

        }
    }

    return;
}
