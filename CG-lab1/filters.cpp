#include"../CG-lab1/filters.h"
#include<fstream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<omp.h>
float limit_color(float color)
{
	if (color < 0.f)
		return 0.f;
	if (color > 255.f)
		return 255.f;
	return color;
}
int limit_pixel(int pix, int x)
{
	if (pix < 0)
		return 0;
	if (pix >= x)
		return x - 1;
	return pix;
}
QImage invers(const QImage& image)
{
	QImage res = image;
	for (int x = 0; x < res.width(); x++)
	{
		for (int y = 0; y < res.height(); y++)
		{
			QColor col = res.pixelColor(x, y);
			col.setRgb(255 - col.red(), 255 - col.green(), 255 - col.blue());
			res.setPixelColor(x,y,col);
		}
	}
	return res;
}
QImage matrix(const QImage& image,std::string name_filt, char* name_file)
{
	QImage res = image;
	int n = 0, m = 0;
	float** matrix;
	float norm = 0.f;
	if (name_file!=NULL)
	{
		char str[MAX_SIZE];
		std::ifstream ifs(name_file);
		ifs.getline(str, MAX_SIZE, '\n');
		n = str[0] - '0';
		m = str[2] - '0';
		matrix = new float* [n];
		for (int i = 0; i < n; i++)
			matrix[i] = new float[m];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (j != m - 1)
					ifs.getline(str, MAX_SIZE, ' ');
				else
					ifs.getline(str, MAX_SIZE, '\n');
				matrix[i][j] = std::atof(str);
				norm += matrix[i][j];
			}
		}
		if (!norm)
			norm = 1.f;
	}
	else
	{
		if (name_filt == "Blur")
		{
			n = BLUR_SIZE;
			m = BLUR_SIZE;
			matrix = new float* [n];
			norm = n * m;
			for (int i = 0; i < n; i++)
			{
				matrix[i] = new float[m];
				for (int j = 0; j < m; j++)
				{
					matrix[i][j] = 1.0 / norm;
				}
			}
			norm = 1.0;
		}
		if (name_filt == "Gauss")
		{
			n = GAUSS_SIZE;
			m = GAUSS_SIZE;
			matrix = new float* [n];
			for (int i = 0; i < n; i++)
			{
				matrix[i] = new float[m];
				for (int j = 0; j < m; j++)
				{
					float tmp = -1.f * (i - n / 2) * (i - n / 2) + (j - m / 2) * (j - m / 2);
					matrix[i][j] = std::exp( tmp / (sigma * sigma));
					norm += matrix[i][j];
				}
			}
		}
	}
	std::pair<int, int> center;
	center.first = n / 2;
	center.second = m / 2;
	for (int x = 0; x < res.width(); x++)
	{
		for (int y = 0; y < res.height(); y++)
		{
			std::pair<int, int> tmp;
			tmp.first = x - center.first;
			tmp.second = y - center.second;
			int x_pix = limit_pixel(tmp.first, res.width());
			int y_pix = limit_pixel(tmp.second, res.height());
			float red = 0, green = 0, blue = 0;
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					QColor col = image.pixelColor(x_pix, y_pix);
					red += col.red() * matrix[i][j];
					green += col.green() * matrix[i][j];
					blue += col.blue() * matrix[i][j];
					++tmp.second;
					y_pix = limit_pixel(tmp.second, res.height());
				}
				tmp.second -= m;
				++tmp.first;
				x_pix = limit_pixel(tmp.first, res.width());
				y_pix = limit_pixel(tmp.second, res.height());
			}
			red /= norm;
			green /= norm;
			blue /= norm;
			red = limit_color(red);
			green = limit_color(green);
			blue = limit_color(blue);
			QColor new_color;
			new_color.setRgb(red, green, blue);
			res.setPixelColor(x, y, new_color);
		}
	}
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	return res;
}
QImage GrayScale(const QImage& image)
{
	QImage res = image;
	for (int x = 0; x < res.width(); x++)
	{
		for (int y = 0; y < res.height(); y++)
		{
			QColor new_color;
			float intensity = res.pixelColor(x, y).red() * 0.299 + res.pixelColor(x, y).blue() * 0.114 + res.pixelColor(x, y).green() * 0.587;
			intensity = limit_color(intensity);
			new_color.setRgb(intensity, intensity, intensity);
			res.setPixelColor(x, y, new_color);
		}
	}
	return res;
}
QImage Sephia(const QImage& image)
{
	QImage res = image;
	for (int x = 0; x < res.width(); x++)
	{
		for (int y = 0; y < res.height(); y++)
		{
			QColor new_color;
			float intensity = res.pixelColor(x, y).red() * 0.299 + res.pixelColor(x, y).blue() * 0.114 + res.pixelColor(x, y).green() * 0.587;
			new_color.setRgb(limit_color(intensity + 2 * sephia), limit_color(intensity + 0.5 * sephia), limit_color(intensity - sephia));
			res.setPixelColor(x, y, new_color);
		}
	}
	return res;
}
QImage Brigntness(const QImage& image)
{
	QImage res = image;
	for (int x = 0; x < res.width(); x++)
	{
		for (int y = 0; y < res.height(); y++)
		{
			QColor new_color;
			float red = res.pixelColor(x, y).red() + brightness;
			red = limit_color(red);
			float green= res.pixelColor(x, y).green() + brightness;
			green = limit_color(green);
			float blue = res.pixelColor(x, y).blue() + brightness;
			blue = limit_color(blue);
			new_color.setRgb(red, green, blue);
			res.setPixelColor(x, y, new_color);
		}
	}
	return res;
}
QImage median(const QImage& image)
{
	QImage res = image;
	for (int x = 0; x < res.width(); x++)
	{
		for (int y = 0; y < res.height(); y++)
		{
			int x_pix = limit_pixel(x - med / 2, res.width());
			int y_pix = limit_pixel(y - med / 2, res.height());
			std::vector<float> red, green, blue;
			for (int i = 0; i < med; i++)
			{
				x_pix = limit_pixel(x - med / 2 + i, res.width());
				for (int j = 0; j < med; j++)
				{
					y_pix = limit_pixel(y - med / 2 + j, res.height());
					red.push_back(image.pixelColor(x_pix, y_pix).red());
					blue.push_back(image.pixelColor(x_pix, y_pix).blue());
					green.push_back(image.pixelColor(x_pix, y_pix).green());
				}
			}
			std::sort(red.begin(), red.end());
			std::sort(green.begin(), green.end());
			std::sort(blue.begin(), blue.end());
			QColor new_color;
			new_color.setRgb(red[(med * med - 1) / 2], green[(med * med - 1) / 2], blue[(med * med - 1) / 2]);
			res.setPixelColor(x, y, new_color);
		}
	}
	return res;
}
QImage dilation(const QImage& image)
{
	QImage res = image;
	for (int x = 0; x < res.width(); x++)
	{
		for (int y = 0; y < res.height(); y++)
		{
			int x_pix = limit_pixel(x - med / 2, res.width());
			int y_pix = limit_pixel(y - med / 2, res.height());
			int red = 0, green = 0, blue = 0;
			for (int i = 0; i < med; i++)
			{
				x_pix = limit_pixel(x - med / 2 + i, res.width());
				for (int j = 0; j < med; j++)
				{
					y_pix = limit_pixel(y - med / 2 + j, res.height());
					red = std::max(red, res.pixelColor(x_pix, y_pix).red());
					green = std::max(green, res.pixelColor(x_pix, y_pix).green());
					blue = std::max(blue, res.pixelColor(x_pix, y_pix).blue());
				}
			}
			QColor new_color;
			new_color.setRgb(red, green, blue);
			res.setPixelColor(x, y, new_color);
		}
	}
	return res;
}
QImage erosion(const QImage& image)
{
	QImage res = image;
	for (int x = 0; x < res.width(); x++)
	{
		for (int y = 0; y < res.height(); y++)
		{
			int x_pix = limit_pixel(x - med / 2, res.width());
			int y_pix = limit_pixel(y - med / 2, res.height());
			int red = 255, green = 255, blue = 255;
			for (int i = 0; i < med; i++)
			{
				x_pix = limit_pixel(x - med / 2 + i, res.width());
				for (int j = 0; j < med; j++)
				{
					y_pix = limit_pixel(y - med / 2 + j, res.height());
					red = std::min(red, res.pixelColor(x_pix, y_pix).red());
					green = std::min(green, res.pixelColor(x_pix, y_pix).green());
					blue = std::min(blue, res.pixelColor(x_pix, y_pix).blue());
				}
			}
			QColor new_color;
			new_color.setRgb(red, green, blue);
			res.setPixelColor(x, y, new_color);
		}
	}
	return res;
}