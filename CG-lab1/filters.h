#pragma once
#include<iostream>
#include<QImage>
const double PI = 3.141592;
const int MAX_SIZE = 10;
const int BLUR_SIZE = 5;
const int GAUSS_SIZE = 7;
const float sigma = 2.f;
const float sephia = 15.f;
const float brightness = 50.f;
const int med = 5;
const int motion_blur = 7;
const int gist = 3;
template<class T, class T2>
T max(T2 a, T b);
template<class T, class T2>
T min(T2 a, T b);
float limit_color(float color);
int limit_pixel(int pix, int x);
QImage invers(const QImage& im);
QImage matrix(const QImage& im, std::string name_filt, char* name_file=NULL);
QImage GrayScale(const QImage& image);
QImage Sephia(const QImage& image);
QImage Brigntness(const QImage& image);
QImage median(const QImage& image);
QImage dilation(const QImage& image, char* name_file);
QImage erosion(const QImage& image, char* name_file);
QImage waves(const QImage& image);
QImage transfer(const QImage& image);
QImage turn(const QImage& image);
QImage lin_gist(const QImage& image);
QImage perfect_refl(const QImage& image);
QImage sobel_filt(const QImage& image, char* file_name1, char* file_name2);
QImage grad(const QImage& image, char* file_name);