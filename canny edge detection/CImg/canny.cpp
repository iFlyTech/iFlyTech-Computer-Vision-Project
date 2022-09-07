#include "canny.h"
#define M_PI       acos(-1.0)

canny::canny(string filename)
{
	img.load_bmp(filename.c_str());
	if (!img.data()) // Check for invalid input
	{
		cout << "Could not open or find the image" << endl;
	}
	else
	{
		vector<vector<double>> filter = createFilter(3, 3, 1);

		//Print filter
		for (int i = 0; i < filter.size(); i++)
		{
			for (int j = 0; j < filter[i].size(); j++)
			{
				cout << filter[i][j] << " ";
			}
		}

		img.save("./result/Original.bmp");

		grayscaled = toGrayScale(); //Grayscale the image
		grayscaled.save("./r