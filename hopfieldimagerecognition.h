#ifndef HOPFIELDIMAGERECOGNITION_H
#define HOPFIELDIMAGERECOGNITION_H

#include <iostream>
#include <vector>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

class HopfieldImageRecognition
{
private:
    int width;
    int height;
    int pixels;
    int size;
    vector<mat> images;
    mat image;
    mat weight;
    int iteration;
    vector<int> hopfieldRandom;
    bool change;
    int getHopfielRandomOrExit();
public:
    HopfieldImageRecognition();
    void setImages(char *filename);
    void showImages();
    void setImage(char *fileName);
    void showImage();
    void nextStep();
    int getIteration();
    void createWeightMatrix();
};

#endif // HOPFIELDIMAGERECOGNITION_H
