#include "Screen.h"

void find_pixel_index_dbg(BYTE* screenBuffer, unsigned int bufferSize)
{
    // (1 pixel) <-- currently using
    unsigned int pixelToFind = 0xFFFFFFFF;

    // (2 pixels)                     //B-G-R-A-B-G-R-A-
    unsigned long long pixelsToFind = 0xFFFFFFFFFFFFFFFF;
                                      //^first  ^-second (pixel)

    for (unsigned int i = 0; i < bufferSize; i += 4)
    {
        // BGRA format
        auto pixelBGRA = (int)((unsigned char)screenBuffer[i] << 24 |
                               (unsigned char)screenBuffer[i + 1] << 16 |
                               (unsigned char)screenBuffer[i + 2] << 8 |
                               (unsigned char)screenBuffer[i + 3]);

        if (pixelBGRA == pixelToFind)
        {
            // found pixel, check the i to get the index of the blue channel
        }


        // or RGBA format
        auto pixelRGBA = (int)((unsigned char)screenBuffer[i + 2] << 24 |
                               (unsigned char)screenBuffer[i + 1] << 16 |
                               (unsigned char)screenBuffer[i] << 8 |
                               (unsigned char)screenBuffer[i + 3]);

        if (pixelRGBA == pixelToFind)
        {
            // found pixel, check the i to get the index of the red channel
        }
    }

    // (multiple pixels)
    const unsigned int pixelsAmount = 4;            //B-    G-    R-    A-    CHANNEL
    BYTE multiplePixelsToFind[pixelsAmount * 4] = { 0xFF, 0xFF, 0xFF, 0xFF,
                                                    0xFF, 0xFF, 0xFF, 0xFF,
                                                    0xFF, 0xFF, 0xFF, 0xFF,
                                                    0xFF, 0xFF, 0xFF, 0xFF, };

    for (unsigned int i = 0; i < bufferSize; i += pixelsAmount * 4)
    {
        BYTE buffer[pixelsAmount * 4] = {};
        memcpy(buffer, screenBuffer + i, sizeof(buffer));
        int result = memcmp(buffer, multiplePixelsToFind, sizeof(buffer));

        if (result == 0)
        {
            // Both 16 byte arrays are identical (returned 0)
        }
    }
}

int main()
{
    Screen screen = Screen();
    BYTE* screenBuffer = nullptr;

    unsigned int pattern1 = 0x595349FF; // BGRA FORMAT
    unsigned int pattern2 = 0x495359FF; // RGBA FORMAT

    while (true)
    {
        screenBuffer = screen.GetPixelBuffer();

        // while not debugging the first GetPixelBuffer() invocation always returns no data, i dont know why, idc tbh
        if (screenBuffer[0] == '\0')
        {
            continue;
        }

        // If you dont have an alpha channel just parse it as FF (255) like in the variables above.
        // Note that the position of the alpha channels remains unchanged.
        // This sample uses DXGI_FORMAT_B8G8R8A8_UNORM format (32 bit / 4 byte each pixel),
        // parse your pixel bytes in the following order: BLUE (0) GREEN (1) RED (2) ALPHA (3)
        unsigned int pixel1 = (unsigned int)((unsigned char)screenBuffer[0] << 24 |
                                             (unsigned char)screenBuffer[1] << 16 |
                                             (unsigned char)screenBuffer[2] << 8 |
                                             (unsigned char)screenBuffer[3]);

        // or if you define a pixel in RGBA format parse it this way: RED(2) GREEN (1) BLUE (0) ALPHA (3)
        unsigned int pixel2 = (unsigned int)((unsigned char)screenBuffer[2] << 24 |
                                             (unsigned char)screenBuffer[1] << 16 |
                                             (unsigned char)screenBuffer[0] << 8 |
                                             (unsigned char)screenBuffer[3]);

        // Compare pixels, in this example, both pixels will be the same.
        if (pixel1 == pattern1 && pixel2 == pattern2)
        {
            // Do your stuff here...
        }

        // Helper function for finding pixel position where i is the index of the first byte (B Channel) of your pixel.
        // This example only checks the first pixel of the screen, use this function to retrieve the position of your desired pixel.
        // Also keep in mind that you will most likely find the pixel multiple times on your screen.
        // Consider using long (8 bytes / 2 pixels) or byte array to get a more unique byte pattern to search with.
            
        //int sizeOfBuffer = screen.outputDuplDesc.ModeDesc.Height * screen.resource.RowPitch;
        //find_pixel_index_dbg(screenBuffer, sizeOfBuffer);
        
        
    }
    return 0;
}