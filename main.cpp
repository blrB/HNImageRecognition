#include <iostream>

#include "hopfieldimagerecognition.h"

using namespace std;

char *images;
char *image;

int main(int argc , char *argv[]){
    if (argc != 3) {
        printf("Not correct argument\n");
        exit(1);
    }
    images = strdup(argv[1]);
    image = strdup(argv[2]);
    HopfieldImageRecognition model;
    model.setImages(images);
    model.showImages();
    model.createWeightMatrix();
    model.setImage(image);
    model.showImage();
    int makeStep = 1;
    do {
        cout << "How many step make?" << endl;
        cin >> makeStep;
        for (int step = 0; step < makeStep; step++){
            model.nextStep();
        }
        model.showImage();
        cout << "Iteration: " << model.getIteration() << endl;
    } while (makeStep > 0);
    return 0;
}

