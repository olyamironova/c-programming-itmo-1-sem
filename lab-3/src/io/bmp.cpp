#include <fstream>
#include <iostream>
#include <cmath>
#include "sandpile.h"

void ExportImage(const Sandpile& sandpile, const std::string& path) {

    std::cout << "Exporting: " << path << '\n';

    int paddingAmount = (sandpile.width / 2 + sandpile.width % 2) % 4;

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int colorHeaderSize = 64;

    const int fileSize = colorHeaderSize + fileHeaderSize + informationHeaderSize + (sandpile.height * sandpile.width) / 2  + paddingAmount * sandpile.height;
    const int bitmapSize = (int)std::ceil((double)(sandpile.width * sandpile.height)/ 2.0) + paddingAmount * sandpile.height;

    unsigned char* fileHeader = new unsigned char[fileHeaderSize]{0};

    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);

    fileHeader[10] = colorHeaderSize + fileHeaderSize + informationHeaderSize;


    unsigned char* informationHeader = new unsigned char[informationHeaderSize]{0};

    informationHeader[0] = (unsigned char)(informationHeaderSize);

    informationHeader[4] = (unsigned char)(sandpile.width);
    informationHeader[5] = (unsigned char)(sandpile.width >> 8);
    informationHeader[6] = (unsigned char)(sandpile.width >> 16);
    informationHeader[7] = (unsigned char)(sandpile.width >> 24);

    informationHeader[8]  = (unsigned char)(sandpile.height);
    informationHeader[9]  = (unsigned char)(sandpile.height >> 8);
    informationHeader[10] = (unsigned char)(sandpile.height >> 16);
    informationHeader[11] = (unsigned char)(sandpile.height >> 24);

    informationHeader[12] = (unsigned char)(1);
    informationHeader[14] = (unsigned char)(4);

    informationHeader[20] = (unsigned char)(bitmapSize);
    informationHeader[21] = (unsigned char)(bitmapSize >> 8);
    informationHeader[22] = (unsigned char)(bitmapSize >> 16);
    informationHeader[23] = (unsigned char)(bitmapSize >> 24);

    informationHeader[32] = (unsigned char)(16);

    unsigned char* colorHeader = new unsigned char[colorHeaderSize]{0};

    colorHeader[0] = 0xff;
    colorHeader[1] = 0xff;
    colorHeader[2] = 0xff;    // white
    colorHeader[3] = 0x0;

    colorHeader[4] = 0x0;
    colorHeader[5] = 0xff;
    colorHeader[6] = 0x0;     // green
    colorHeader[7] = 0x0;

    colorHeader[8]  = 0x0;
    colorHeader[9]  = 0xff;   // yellow
    colorHeader[10] = 0xff;
    colorHeader[11] = 0x0;

    colorHeader[12] = 0xff;
    colorHeader[13] = 0x0;
    colorHeader[14] = 0xff;  // violet
    colorHeader[15] = 0x0;

    colorHeader[16] = 0x0;
    colorHeader[17] = 0x0;   // black
    colorHeader[18] = 0x0;
    colorHeader[19] = 0x0;

    std::ofstream file;
    file.open(path.c_str(), std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Couldn't create file" << std::endl;
        exit(1);
    }

    file.write((char *)fileHeader, fileHeaderSize);
    file.write((char *)informationHeader, informationHeaderSize);
    file.write((char *)colorHeader, colorHeaderSize);

    unsigned char pixel1;
    unsigned char pixel2;


    char* bmpPad;
    if(paddingAmount){
        paddingAmount = 4 - paddingAmount;
        bmpPad = new char[paddingAmount]{0};
    }


    for (int y = 0; y < sandpile.height; y++) {
        for (int x = 0; x < sandpile.width; x++) {
            pixel1 = (unsigned char)sandpile.grid[y][x++];
            pixel2 = (unsigned char)0;

            if(x < sandpile.width)
                pixel2 = (unsigned char)sandpile.grid[y][x];


            pixel1 = pixel1 > 4 ? 4 : pixel1;
            pixel2 = pixel2 > 4 ? 4 : pixel2;


            unsigned char color[] = {static_cast<unsigned char>(((pixel1 << 4) | pixel2))};
            file.write((char *)(color), 1);
        }
        if(paddingAmount){
            file.write(bmpPad, paddingAmount);
        }
    }

    file.close();
    if(paddingAmount){
        delete[] bmpPad;
    }
    delete[] fileHeader;
    delete[] informationHeader;
    delete[] colorHeader;
}