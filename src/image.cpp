//
// Created by Xian Zhang on 11/16/2021.
//
#include <fstream>
#include <iostream>
#include "image.h"
image::image(image* image1) {
    this->filename = image1->filename;
    std::ifstream inStream(this->filename, std::ios::binary);
    inStream.read(&this->head.idLength, sizeof(head.idLength));
    inStream.read(&this->head.colorMapType, sizeof(head.colorMapType));
    inStream.read(&this->head.dataTypeCode, sizeof(head.dataTypeCode));
    inStream.read((char *) &this->head.colorMapLength, sizeof(head.colorMapLength));
    inStream.read((char *) &this->head.colorMapOrigin, sizeof(head.colorMapOrigin));
    inStream.read(&this->head.colorMapDepth, sizeof(head.colorMapDepth));
    inStream.read((char *) &this->head.xOrigin, sizeof(head.xOrigin));
    inStream.read((char *) &this->head.yOrigin, sizeof(head.yOrigin));
    inStream.read((char *) &this->head.width, sizeof(head.width));
    inStream.read((char *) &this->head.height, sizeof(head.height));
    inStream.read(&this->head.bitsPerPixel, sizeof(head.bitsPerPixel));
    inStream.read(&this->head.imageDescriptor, sizeof(head.imageDescriptor));
    this->size = this->head.width * this->head.height * 3;
    this->fileData = new unsigned char[this->size];
}

void image::readData(std::string file1){
    this->filename = file1;
    std::ifstream inStream(file1, std::ios::binary);
    inStream.read(&this->head.idLength, sizeof(head.idLength));
    inStream.read(&this->head.colorMapType, sizeof(head.colorMapType));
    inStream.read(&this->head.dataTypeCode, sizeof(head.dataTypeCode));
    inStream.read((char *) &this->head.colorMapLength, sizeof(head.colorMapLength));
    inStream.read((char *) &this->head.colorMapOrigin, sizeof(head.colorMapOrigin));
    inStream.read(&this->head.colorMapDepth, sizeof(head.colorMapDepth));
    inStream.read((char *) &this->head.xOrigin, sizeof(head.xOrigin));
    inStream.read((char *) &this->head.yOrigin, sizeof(head.yOrigin));
    inStream.read((char *) &this->head.width, sizeof(head.width));
    inStream.read((char *) &this->head.height, sizeof(head.height));
    inStream.read(&this->head.bitsPerPixel, sizeof(head.bitsPerPixel));
    inStream.read(&this->head.imageDescriptor, sizeof(head.imageDescriptor));
    this->size = this->head.width * this->head.height * 3;
    this->fileData = new unsigned char[this->size];
    inStream.read((char*) (this->fileData),  (this->size));
}


