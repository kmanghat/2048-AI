#include "loadBMP.h"

unsigned int reorderBytes(byte *arr)
{
    unsigned int b0 = arr[0];
    unsigned int b1 = arr[1];
    unsigned int b2 = arr[2];
    unsigned int b3 = arr[3];
    int big = (b0 | b1 << 8 | b2 << 16 | b3 << 24);
    return big;
}

/**************************************************************************//**
 * Load in the game tiles in png format and decode them for display as RGB
 *
 * @param[in]  imagepath - path to the images
 * @param[out] width     - the width of the image being loaded
 * @param[out] height    - the height of the image being loaded
 * @param[out] image     - The image bytes
 * @returns true iff the load was successful
 *****************************************************************************/
bool loadBMP(const char *imagepath, int &width, int &height, unsigned char *&image)
{
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;

    FILE *file = fopen(imagepath, "rb");
    if (!file)
    {
        std::cout << "Image at " << imagepath << " could not be opened\n";
        return false;
    }

    if (fread(header, 1, 54, file) != 54)
    {
        std::cout << "Header invalid: Not a BMP file\n";
        return false;
    }

    if (header[0] != 'B' || header[1] != 'M')
    {
        std::cout << "Incorrect image identifier.  Not a BMP file!\n";
        return false;
    }

    dataPos = reorderBytes(&header[0x0A]);
    imageSize = reorderBytes(&header[0x22]);
    width = reorderBytes(&header[0x12]);
    height = reorderBytes(&header[0x16]);

    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;

    image = new unsigned char[imageSize];
    if (fread(image, 1, imageSize, file) == 0)
        std::cerr << "Can't load image from " << imagepath << std::endl;

    fclose(file);
    return true;
}
