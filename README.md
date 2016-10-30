# Artificial Neural Networks (ANN) Image Recognition

Hopfield network (HN) for laboratory work.

## Library

<a href="http://arma.sourceforge.net/docs.html/">Armadillo C++ linear algebra library</a>

for Ubuntu:

```sh
sudo apt-get install libarmadillo-dev libarmadillo6
```
Before installing Armadillo, it's recommended to install LAPACK, BLAS and ATLAS

## Example

```sh
./HopfieldImageRecognition images.txt image_with_noise.txt
```


Input images
<p align="center">
  <img src="https://raw.githubusercontent.com/blrB/HNImageRecognition/master/imageText/original.png" alt="Input"/>
</p>

Input image with noise(one by one)
<p align="center">
  <img src="https://raw.githubusercontent.com/blrB/HNImageRecognition/master/imageText/noisy.png" alt="Input"/>
</p>

Output image with noise(one by one)
<p align="center">
  <img src="https://raw.githubusercontent.com/blrB/HNImageRecognition/master/imageText/original.png" alt="Input"/>
</p>
