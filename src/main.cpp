#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
#include <cmath>


//Writes the header to the file from the image instance
void writeData(std::string file, image* image1){
    std::ofstream inStream(file, std::ios::binary);
    inStream.write((char *) &image1->head.idLength, sizeof(image1->head.idLength));
    inStream.write((char *) &image1->head.colorMapType, sizeof(image1->head.colorMapType));
    inStream.write((char *) &image1->head.dataTypeCode, sizeof(image1->head.dataTypeCode));
    inStream.write((char *) &image1->head.colorMapLength, sizeof(image1->head.colorMapLength));
    inStream.write((char *) &image1->head.colorMapOrigin, sizeof(image1->head.colorMapOrigin));
    inStream.write((char *) &image1->head.colorMapDepth, sizeof(image1->head.colorMapDepth));
    inStream.write((char *) &image1->head.xOrigin, sizeof(image1->head.xOrigin));
    inStream.write((char *) &image1->head.yOrigin, sizeof(image1->head.yOrigin));
    inStream.write((char *) &image1->head.width, sizeof(image1->head.width));
    inStream.write((char *) &image1->head.height, sizeof(image1->head.height));
    inStream.write((char *) &image1->head.bitsPerPixel, sizeof(image1->head.bitsPerPixel));
    inStream.write((char *) &image1->head.imageDescriptor, sizeof(image1->head.imageDescriptor));
    inStream.write((char *) image1->fileData, (image1->size));
}

image* multiply(image* image1, image* image2){
    image* image3 = new image(image1);
    for (int x = 0; x < image3->getSize(); x++){
        image3->fileData[x] = (unsigned char) round((double)image1->fileData[x]/(255.0) * double(image2->fileData[x])/(255.0) * 255.0);
    }
    return(image3);
}

image* subtract(image* image1, image* image2){
    image* image3 = new image(image1);
    for (int x = 0; x < image3->getSize(); x++){
        double newValue = ((double)image2->fileData[x] - double(image1->fileData[x]));
        (newValue < 0) ? image3->fileData[x]=0 : image3->fileData[x]= (unsigned short) newValue;
    }
    return(image3);
}

image* screenblend(image* image1, image* image2){
    image* image3 = new image(image1);
    for (int x = 0; x < image3->getSize(); x++){
        double newValue =round((1-(1-(double)image1->fileData[x]/255.0) * (1-((double)image2->fileData[x]/255.0)))*255.0);
        image3->fileData[x] = (unsigned short) newValue;
    }
    return(image3);
}
image* overlay(image* image1, image* image2){
    image* image3 = new image(image1);
    for (int x = 0; x < image3->getSize(); x++){
        if ((double)image2->fileData[x]/255.0 <= 0.5){
            double newValue = round(2* (double) image1->fileData[x]/255.0 * (double) image2->fileData[x]/255.0 *255.0);
            image3->fileData[x] = (unsigned short) newValue;
        } else {
            double newValue = round((1 - 2.0*(1-(double)(image1->fileData[x])/255.0)*(1-(double)(image2->fileData[x])/255.0))*255.0);
            image3->fileData[x] = (unsigned short) newValue;
        }
    }
    return(image3);
}

bool testing(image* image1, image* image2){
    bool isSame = true;
    for (int x = 0; x < image1->getSize(); x++){
        if (image1->fileData[x] != image2->fileData[x]){
            isSame = false;
            std::cout << "Mismatch: value 1 = " << (int) image1->fileData[x] << " value 2 = " << (int) image2->fileData[x] << std::endl;
            std::cout << "Index: " << x << std::endl;
            break;
        }
    }
    return isSame;
}

int main() {
    //The first problem
    image* image1 = new image("input/layer1.tga");
    image* image2 = new image("input/pattern1.tga");
    image* image3 = multiply(image1, image2);
    writeData("output/part1.tga", image3);
    image* testCase3 = new image("examples/EXAMPLE_part1.tga");
    if (testing(image3, testCase3)){
        std::cout << "Test #1 Passed!" << std::endl;
    } else {
        std::cout << "Test #1 Failed!" << std::endl;
    }
    delete image1, delete image2, delete image3, delete testCase3;

    //Number 2
    image* image4 = new image("input/layer2.tga");
    image* image5 = new image("input/car.tga");
    image* image6 = subtract(image4, image5);
    writeData("output/part2.tga", image6);
    image* testCase6 = new image("examples/EXAMPLE_part2.tga");
    if (testing(image6, testCase6)){
        std::cout << "Test #2 Passed!" << std::endl;
    } else {
        std::cout << "Test #2 Failed!" << std::endl;
    }
    delete image4, delete image5, delete image6, delete testCase6;
    //Number 3

    image* image7 = new image("input/layer1.tga");
    image* image8 = new image("input/pattern2.tga");
    image* temp = multiply(image7, image8);
    image* image9 = new image("input/text.tga");
    image* image10 = screenblend(image9, temp);
    writeData("output/part3.tga", image10);
    image* testCase10 = new image("examples/EXAMPLE_part3.tga");
    if (testing(image10, testCase10)){
        std::cout << "Test #3 Passed!" << std::endl;
    } else {
        std::cout << "Test #3 Failed!" << std::endl;
    }
    delete image7, delete image8, delete temp, delete image9, delete image10, delete testCase10;

    //Number 4
    image* image11 = new image("input/layer2.tga");
    image* image12 = new image("input/circles.tga");
    image* multiplied = multiply(image11, image12);
    image* image13 = new image("input/pattern2.tga");
    image* image14 = subtract(image13, multiplied);
    writeData("output/part4.tga", image14);
    image* testCase14 = new image("examples/EXAMPLE_part4.tga");
    if (testing(image14, testCase14)){
        std::cout << "Test #4 Passed!" << std::endl;
    } else {
        std::cout << "Test #4 Failed!" << std::endl;
    }
    delete image11, delete image12, delete multiplied, delete image13, delete image14, delete testCase14;

    //Now number 5, I never wanna hear you say!!!
    image* image15 = new image("input/layer1.tga");
    image* image16 = new image("input/pattern1.tga");
    image* image17 = overlay(image15, image16);
    writeData("output/part5.tga", image17);
    image* testCase17= new image("examples/EXAMPLE_part5.tga");
    if (testing(image17, testCase17)){
        std::cout << "Test #5 Passed!" << std::endl;
    } else {
        std::cout << "Test #5 Failed!" << std::endl;
    }
    delete image15, delete image16, delete image17, delete testCase17;

    //Number 6
    image* image18 = new image("input/car.tga");
    for (int x = 1; x < image18->getSize() + 1; x+=3){
        double value = (double) image18->fileData[x] + 200.0;
        (value > 255) ? image18->fileData[x] = 255: image18->fileData[x] = value;
    }
    writeData("output/part6.tga", image18);
    image* testCase18 = new image("examples/EXAMPLE_part6.tga");
    if (testing(image18, testCase18)){
        std::cout << "Test #6 Passed!" << std::endl;
    } else {
        std::cout << "Test #6 Failed!" << std::endl;
    }
    delete image18, delete testCase18;

    //Number 7
    image* image19 = new image("input/car.tga");
    for (int x = 0; x < image19->getSize() + 1; x+=3){
        image19->fileData[x] = 0;
        double value = (double) image19->fileData[x+2]*4;
        (value > 255) ? image19->fileData[x+2] = 255: image19->fileData[x+2] = value;
    }
    writeData("output/part7.tga", image19);
    image* testCase19 = new image("examples/EXAMPLE_part7.tga");
    if (testing(image19, testCase19)){
        std::cout << "Test #7 Passed!" << std::endl;
    } else {
        std::cout << "Test #7 Failed!" << std::endl;
    }
    delete image19, delete testCase19;

    //Number 8
    image* image20 = new image("input/car.tga");
    image* image21 = new image("input/car.tga");
    image* image22 = new image("input/car.tga");
    for (int x = 0; x < image20->getSize(); x+=3){
        image20->fileData[x] = image20->fileData[x+2];
        image20->fileData[x+1] = image20->fileData[x+2];
        image21->fileData[x] = image21->fileData[x+1];
        image21->fileData[x+2] = image21->fileData[x+1];
        image22->fileData[x+1] = image22->fileData[x];
        image22->fileData[x+2] = image22->fileData[x];
    }
    writeData("output/part8_r.tga", image20);
    writeData("output/part8_g.tga", image21);
    writeData("output/part8_b.tga", image22);
    image* testCase20 = new image("examples/EXAMPLE_part8_r.tga");
    image* testCase21 = new image("examples/EXAMPLE_part8_g.tga");
    image* testCase22 = new image("examples/EXAMPLE_part8_b.tga");
    if (testing(image20, testCase20) && testing(image21, testCase21) && testing(image22, testCase22)){
        std::cout << "Test #8 Passed!" << std::endl;
    } else {
        std::cout << "Test #8 Failed!" << std::endl;
    }
    delete image20, delete image21, delete image22, delete testCase20, delete testCase21, delete testCase22;

    //number 9
    image* image23 = new image("input/layer_red.tga");
    image* image24 = new image("input/layer_green.tga");
    image* image25 = new image("input/layer_blue.tga");
    image* solutionImg = new image("input/layer_red.tga");
    for (int x = 0; x < image23->getSize(); x+=3){
        solutionImg->fileData[x] = image25->fileData[x];
        solutionImg->fileData[x+1] = image24->fileData[x+1];
        solutionImg->fileData[x+2] = image23->fileData[x+2];
    }
    writeData("output/part9.tga", solutionImg);
    image* testCasesolutionImg = new image("examples/EXAMPLE_part9.tga");
    if (testing(solutionImg, testCasesolutionImg)){
        std::cout << "Test #9 Passed!" << std::endl;
    } else {
        std::cout << "Test #9 Failed!" << std::endl;
    }
    delete image23, delete image24, delete image25, delete solutionImg, delete testCasesolutionImg;

    //Number 10
    image* image26 = new image("input/text2.tga");
    image* image26Sol = new image("input/text2.tga");
    for (int x = 0; x < image26->getSize(); x+=3){
        image26Sol->fileData[x] = image26->fileData[image26->getSize()-3-x];
        image26Sol->fileData[x+1] = image26->fileData[image26->getSize()-2-x];
        image26Sol->fileData[x+2] = image26->fileData[image26->getSize()-1-x];
    }
    writeData("output/part10.tga", image26Sol);
    image* testCase26 = new image("examples/EXAMPLE_part10.tga");
    if (testing(image26Sol, testCase26)){
        std::cout << "Test #10 Passed!" << std::endl;
    } else {
        std::cout << "Test #10 Failed!" << std::endl;
    }
    delete image26, delete image26Sol, delete testCase26;

    //Extra credit
    image* extraCredit = new image("input/car.tga");
    image* image27 = new image("input/text.tga");
    image* image28 = new image("input/pattern1.tga");
    image* image29 = new image("input/car.tga");
    image* image30 = new image("input/circles.tga");
    extraCredit->head.height = (int)image27->head.height*2;
    extraCredit->head.width = (int)image27->head.width*2;
    extraCredit->size = (int)extraCredit->head.width * (int)extraCredit->head.height * 3;
    delete[] extraCredit->fileData;

    extraCredit->fileData = new unsigned char[extraCredit->size];
    int pivot = 0;
    int ogIndex = 0;
    for (int x = 0; x <image27->head.width;  x++){
        for (int y = 0; y < image27->head.height*3; y++){
            extraCredit->fileData[pivot] = image27->fileData[ogIndex];
            pivot++;
            ogIndex ++;//For the origin array to paste into the larger array
        }
        pivot = pivot + (extraCredit->head.width/2)*3;
    }
    //Setting the pivot again
    pivot = (extraCredit->head.width/2)*3;
    ogIndex = 0;
    for (int x = 0; x <image28->head.width;  x++){
        for (int y = 0; y < image28->head.height*3; y++){
            extraCredit->fileData[pivot] = image28->fileData[ogIndex];
            ogIndex++;//For the origin array to paste into the larger array
            pivot++;
        }
        pivot = pivot + (extraCredit->head.width/2)*3;
    }

    pivot = (extraCredit->getSize()/2);
    ogIndex = 0;
    for (int x = 0; x <image29->head.width;  x++){
        for (int y = 0; y < image29->head.height*3; y++){
            extraCredit->fileData[pivot] = image29->fileData[ogIndex];
            pivot++;
            ogIndex++;//For the origin array to paste into the larger array
        }
        pivot = pivot + (extraCredit->head.width/2)*3;
    }

    pivot = (extraCredit->getSize()/2) + (extraCredit->head.width/2)*3;
    ogIndex = 0;
    for (int x = 0; x <image30->head.width;  x++){
        for (int y = 0; y < image30->head.height*3; y++){
            extraCredit->fileData[pivot] = image30->fileData[ogIndex];
            pivot++;
            ogIndex++;//For the origin array to paste into the larger array
        }
        pivot = pivot + (extraCredit->head.width/2)*3;
    }
    image* testCaseEC = new image("examples/EXAMPLE_extracredit.tga");
    if (testing(extraCredit, testCaseEC)){
        std::cout << "Test EC Passed!" << std::endl;
    } else {
        std::cout << "Test EC Failed!" << std::endl;
    }
    writeData("output/extracredit.tga", extraCredit);
    delete extraCredit, delete image27, delete image28, delete image29, delete image30, delete testCaseEC;
}