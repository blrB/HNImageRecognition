#include <iostream>
#include <fstream>
#include <vector>
#include <armadillo>

#include "hopfieldimagerecognition.h"

using namespace std;
using namespace arma;


HopfieldImageRecognition::HopfieldImageRecognition(){
    iteration = 0;
    change = true;
}

void HopfieldImageRecognition::setImages(char *fileName){
    ifstream myfile(fileName);
    if (myfile.is_open()){
        myfile >> height;
        myfile >> width;
        pixels = height * width;
        myfile >> size;
        for (int indexImage = 0; indexImage < size; indexImage++){
            vector<double> vector;
            for (int indexPixel = 0; indexPixel < pixels; indexPixel++){
                double pixel;
                myfile >> pixel;
                vector.push_back(pixel);
            }
            images.push_back(mat(vector).t());
        }
    } else{
        cout << "Error open file" << endl;
    }
}

void HopfieldImageRecognition::showImages(){
    cout << "Images:" << endl;
    for (int indexImage = 0; indexImage < size; indexImage++){
        cout << "Image [" << indexImage + 1 << "]:" << endl;
        for (int indexPixel = 0; indexPixel < pixels; indexPixel++){
            cout << ((images.at(indexImage)(0,indexPixel) == 1) ? "#" : ".");
            if ((indexPixel + 1) % width == 0) {
                cout << endl;
            }
        }
        cout << endl;
    }
}

void HopfieldImageRecognition::setImage(char *fileName){
    int h;
    int w;
    ifstream myfile(fileName);
    if (myfile.is_open()){
        myfile >> h;
        myfile >> w;
        if (h != height && w != width){
            cout << "Wrong height or width in image for recognition";
            exit(1);
        }
        vector<double> vector;
        for (int indexPixel = 0; indexPixel < pixels; indexPixel++){
            double pixel;
            myfile >> pixel;
            vector.push_back(pixel);
        }
        image = mat(vector).t();
    } else{
        cout << "Error open file for recognition" << endl;
    }
}

void HopfieldImageRecognition::showImage(){
    cout << endl;
    for (int indexPixel = 0; indexPixel < pixels; indexPixel++){
        cout << ((image(0,indexPixel) == 1) ? "#" : ".");
        if ((indexPixel + 1) % width == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

void HopfieldImageRecognition::nextStep(){
    srand (time(NULL));
    int random = getHopfielRandomOrExit();
    mat S = (image * weight.col(random));
    if (S(0,0) < 0){
        if (image(0, random) != -1){
            image(0,random) = -1;
            change = true;
        }
    } else if (S(0,0) > 0){
        if (image(0, random) != 1){
            image(0,random) = 1;
            change = true;
        }
    } else {
        // image(0,random) /*(t)*/ = image(0,random) /*(t-1)*/
    }
    iteration++;
}

int HopfieldImageRecognition::getHopfielRandomOrExit(){
    srand (time(NULL));
    if (hopfieldRandom.empty()){
        if (change == false){
            cout << "Education completed! Iteration: " << iteration << endl;
            showImage();
            exit(0);
        } else {
            change = false;
        }
        for(int i = 0; i < pixels; i++){
            hopfieldRandom.push_back(i);
        }
        random_shuffle(hopfieldRandom.begin(), hopfieldRandom.end());
    }
    int random = hopfieldRandom.back();;
    hopfieldRandom.pop_back();
    return random;
}

int HopfieldImageRecognition::getIteration(){
    return iteration;
}

void HopfieldImageRecognition::createWeightMatrix(){
    double FACTOR = 0.8; // 0.7..0.9
    double E = 0.0000001;
    int N = pixels + 1;
    double change;
    weight = mat(pixels,pixels,fill::zeros);
    do{
        change = 0;
        for (int indexImage = 0; indexImage < size; indexImage++){
            mat Xi = images.at(indexImage).t();
            mat deltaW = ((FACTOR / N) * (Xi - weight * Xi) * Xi.t());
            change += accu(abs(deltaW));
            weight = weight + deltaW;
        }
    } while (change > E);
}
