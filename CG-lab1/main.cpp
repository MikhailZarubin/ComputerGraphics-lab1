#include<iostream>
#include<QImage>
#include"../CG-lab1/filters.h"
void main(int argc, char* argv[])
{
	QImage image, image_for_gist, image_for_perfect_refl;
	std::string s, sl, sp;
	for (int i = 0; i < argc; i++)
	{
		if (!std::strcmp(argv[i], "-p") && i + 3 < argc)
		{
			s = argv[i + 1];
			sp = argv[i + 2];
			sl = argv[i + 3];
			break;
		}
	}
	image.load(QString(s.c_str()));
	image_for_perfect_refl.load(QString(sp.c_str()));
	image_for_gist.load(QString(sl.c_str()));
	invers(image).save("filt_images/invers.jpg");
	matrix(image,"", "matrix.txt").save("filt_images/matrix.jpg");
    matrix(image, "Blur").save("filt_images/blur.jpg");
	matrix(image, "Gauss").save("filt_images/gauss.jpg");
	GrayScale(image).save("filt_images/GrayScale.jpg");
	Sephia(image).save("filt_images/Sephia.jpg");
	Brigntness(image).save("filt_images/brigntness.jpg");
	matrix(image, "", "sobel_x.txt").save("filt_images/sobel_x.jpg");
	matrix(image, "", "sobel_y.txt").save("filt_images/sobel_y.jpg");
	matrix(image, "", "sharp.txt").save("filt_images/sharp.jpg");
	median(image).save("filt_images/median.jpg");
	QImage dil = dilation(image);
	dil.save("filt_images/dilation.jpg");
	QImage eros = erosion(image);
	eros.save("filt_images/erosion.jpg");
	dilation(eros).save("filt_images/opening.jpg");
	erosion(dil).save("filt_images/closing.jpg");
	matrix(image, "", "oper_sharr_x.txt").save("filt_images/oper_sharr_x.jpg");
    matrix(image, "", "oper_sharr_y.txt").save("filt_images/oper_sharr_y.jpg");
	matrix(image, "motion_blur").save("filt_images/motion_blur.jpg");
	waves(image).save("filt_images/waves.jpg");
	transfer(image).save("filt_images/transfer.jpg");
	turn(image).save("filt_images/turn.jpg");
	lin_gist(image_for_gist).save("filt_images/lin_gist.jpg");
	perfect_refl(image_for_perfect_refl).save("filt_images/perfect_refl.jpg");
}