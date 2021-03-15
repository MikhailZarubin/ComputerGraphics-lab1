#pragma once
#include<iostream>
#include<QImage>
const int MAX_SIZE = 10;
const int BLUR_SIZE = 5;
const int GAUSS_SIZE = 7;
const float sigma = 2.f;
const float sephia = 15.f;
const float brightness = 50.f;
const int med = 3;
float limit_color(float color);
int limit_pixel(int pix, int x);
QImage invers(const QImage& im);
QImage matrix(const QImage& im, std::string name_filt, char* name_file=NULL);
QImage GrayScale(const QImage& image);
QImage Sephia(const QImage& image);
QImage Brigntness(const QImage& image);
QImage median(const QImage& image);
QImage dilation(const QImage& image);
QImage erosion(const QImage& image);
