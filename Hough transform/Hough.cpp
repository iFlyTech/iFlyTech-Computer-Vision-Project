
#include "Hough.h"


Hough::Hough(string filename) {
	img.load(filename.c_str());

	width = img.width();
	height = img.height();
	max_length = sqrt(pow(width, 2) + pow(height, 2));

	/*gFiltered = img.get_norm().normalize(0, 255);
	gFiltered.blur(5);

	Prewitt();*/
	//sobel();
	gradnum.load("./result2/Edge2.bmp");
	result = gradnum;


	/*houghSpaceTransform();
	houghLinesDetect();
	drawLines();
	drawPoints();
	result.save("./result1/6.bmp");*/


	houghCircleTransform();
	result.save("./result2/2.bmp");

}

void Hough::sobel()
{
	//Sobel X Filter
	double x1[] = { 1.0, 0, -1.0 };
	double x2[] = { 2.0, 0, -2.0 };
	double x3[] = { 1.0, 0, -1.0 };

	vector<vector<double>> xFilter(3);
	xFilter[0].assign(x1, x1 + 3);
	xFilter[1].assign(x2, x2 + 3);
	xFilter[2].assign(x3, x3 + 3);

	//Sobel Y Filter
	double y1[] = { -1.0, -2.0, -1.0 };
	double y2[] = { 0, 0, 0 };
	double y3[] = { 1.0, 2.0, 1.0 };

	vector<vector<double>> yFilter(3);
	yFilter[0].assign(y1, y1 + 3);
	yFilter[1].assign(y2, y2 + 3);
	yFilter[2].assign(y3, y3 + 3);

	//Limit Size
	int size = (int)xFilter.size() / 2;

	gradnum=CImg<uchar>(gFiltered.width() - 2 * size, gFiltered.height() - 2 * size, 1, 1);

	for (int i = size; i < gFiltered.width() - size; i++)
	{
		for (int j = size; j < gFiltered.height() - size; j++)
		{
			double sumx = 0;
			double sumy = 0;

			for (int x = 0; x < xFilter.size(); x++)
				for (int y = 0; y < yFilter.size(); y++)
				{
					sumx += yFilter[x][y] * (double)(gFiltered(i + x - size, j + y - size)); //Sobel_X Filter Value
					sumy += xFilter[x][y] * (double)(gFiltered(i + x - size, j + y - size)); //Sobel_Y Filter Value
				}
			double sumxsq = sumx * sumx;
			double sumysq = sumy * sumy;

			double sq2 = sqrt(sumxsq + sumysq);

			if (sq2 > 255) //Unsigned Char Fix
				sq2 = 255;
			if (sq2 > 10)
				gradnum(i - size, j - size) = sq2;
			else
				gradnum(i - size, j - size) = 0;

		}
	}

}

void Hough::Prewitt()
{
	gradnum = CImg<double>(img.width(), img.height(), 1, 1, 0);
	// 定义3*3领域矩阵I  
	CImg_3x3(I, double);
	// 遍历计算梯度值  
	cimg_for3x3(gFiltered, x, y, 0, 0, I, double) {
		const double ix = Inc - Ipc;
		const double iy = Icp - Icn;
		double grad = std::sqrt(ix*ix + iy * iy);
		// 梯度大于阈值才赋值  
		if (grad > gradLimit) {
			gradnum(x, y) = grad;
		}
	}
	
}

void Hough::houghSpaceTransform()
{
	houghImage = CImg<int>(theta, max_length, 1, 1, 0);

	cimg_forXY(gradnum, x, y) {
		int temp = gradnum(x, y);
		if (temp != 0) {
			for (int i = 0; i < theta; ++i) {
				double r = x * cos(i*interval) + y * sin(i*interval);
				if (r >= 0 && r < max_length) {
					houghImage(i, r)++;		//voting
				}
			}
		}
	}
}