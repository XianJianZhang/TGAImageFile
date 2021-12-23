//
// Created by Xian Jian Zhang on 11/16/2021.
//
#include <iostream>
#ifndef PROJECT3ZHANG_IMAGE_H
#define PROJECT3ZHANG_IMAGE_H

#endif //PROJECT3ZHANG_IMAGE_H
class image{
public:
    image(std::string fileName){ readData(fileName);};
    image(image* image1);
    void readData(std::string file);
    int getSize(){return((int)this->size);};
    ~image(){delete [] fileData;};
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapLength;
        short colorMapOrigin;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };
    Header head;
    std::string filename = "";
    int size =0;
    unsigned char* fileData = nullptr;
};