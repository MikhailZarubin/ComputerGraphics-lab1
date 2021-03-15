#include<iostream>
#include<QImage>
#include"../CG-lab1/filters.h"
void main(int argc, char* argv[])
{
	QImage image;
	std::string s;
	for (int i = 0; i < argc; i++)
	{
		if (!std::strcmp(argv[i], "-p") && i + 1 < argc)
			s = argv[i + 1];
	}
	image.load(QString(s.c_str()));
	//invers(image).save("filt_images/invers.jpg");
	//matrix(image,"", "matrix.txt").save("filt_images/matrix.jpg");
	//matrix(image, "Blur").save("filt_images/blur.jpg");
	//matrix(image, "Gauss").save("filt_images/gauss.jpg");
	//GrayScale(image).save("filt_images/GrayScale.jpg");
	//Sephia(image).save("filt_images/Sephia.jpg");
	//Brigntness(image).save("filt_images/brigntness.jpg");
	//matrix(image, "", "sobel_x.txt").save("filt_images/sobel_x.jpg");
	//matrix(image, "", "sobel_y.txt").save("filt_images/sobel_y.jpg");
	//matrix(image, "", "sharp.txt").save("filt_images/sharp.jpg");
	median(image).save("filt_images/median.jpg");
	dilation(image).save("filt_images/dilation.jpg");
	erosion(image).save("filt_images/erosion.jpg");
	dilation(erosion(image)).save("filt_images/opening.jpg");
	erosion(dilation(image)).save("filt_images/closing.jpg");
}