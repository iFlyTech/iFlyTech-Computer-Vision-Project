
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
	// ����3*3�������I  
	CImg_3x3(I, double);
	// ���������ݶ�ֵ  
	cimg_for3x3(gFiltered, x, y, 0, 0, I, double) {
		const double ix = Inc - Ipc;
		const double iy = Icp - Icn;
		double grad = std::sqrt(ix*ix + iy * iy);
		// �ݶȴ�����ֵ�Ÿ�ֵ  
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

double Hough::distance(double x, double y) {
	return sqrt(x*x + y * y);
}

void Hough::houghLinesDetect()
{
	cimg_forXY(houghImage, x, y) {
		if (houghImage(x, y) > min_votes) {
			bool flag = false;
			for (auto& c : peaks) {
				if (distance(c.x - x, c.y - y) < min_distance) {
					flag = true;
					if (houghImage(x, y) > houghImage(c.x, c.y)) {
						c = Point(x, y);
					}
				}
			}
			if (!flag) {
				peaks.push_back(Point(x, y));
			}
		}
	}
	cout << peaks.size() << endl;

}

void Hough::drawLines()
{
	lines.clear();
	for (int i = 0; i < peaks.size(); i++) {
		double theta = double(peaks[i].x)*interval;
		double k = -cos(theta) / sin(theta); // ֱ��б��
		if (peaks[i].x == 90|| peaks[i].x == 270)
			k = 0;
		double b = double(peaks[i].y) / sin(theta);
		Line templine(k, b);
		lines.push_back(templine);
	}
	int x_min = 0, y_min = 0;
	int x_max = img.width() - 1;
	int y_max = img.height() - 1;
	result = img;

	const double lines_color[] = { 0, 0, 255 };
	for (int i = 0; i < lines.size(); i++) {
		const int x0 = (y_min - lines[i].b) / lines[i].k;
		const int x1 = (y_max - lines[i].b) / lines[i].k;
		const int x = peaks[i].y / cos(peaks[i].x*interval);
		const int y = peaks[i].y / sin(peaks[i].x*interval);

		if (peaks[i].x > 0&&peaks[i].x<=360) {	//б�ʴ���
			if (lines[i].k != 0) {	
				result.draw_line(x0, y_min, x1, y_max, lines_color);
				//cout << x0 << " " << y_min << " " << x1 << " " << y_max << endl;
			}
			else {	//б��Ϊ0
				result.draw_line(x_min, y, x_max, y, lines_color);
			}
		}
		else {		//б�ʲ�����
			result.draw_line(x, y_min, x, y_max, lines_color);

			//cout << y_min << " " << x << endl;
		}
	}
}

void Hough::drawPoints()
{
	for (int i = 0; i < peaks.size(); ++i) {
		//cout << "vote: " << houghImage(peaks[i].x, peaks[i].y) << endl;
		cout << "vote: " << peaks[i].x<<" "<<peaks[i].y << endl;

		double angle = peaks[i].x*interval;
		double a0 = cos(angle), b0 = sin(angle), c0 = -peaks[i].y;
		//cout <<"Peaks "<< peaks[i].x << " "<<peaks[i].y << endl;
		if (peaks[i].x == 90)
			a0 = 0;
		cout << "Line"<<i<< ": ( "<< a0 <<" ) x + (" << b0 << ") y + ( "<< c0 <<" ) = 0"<< endl;

		for (int j = i + 1; j < peaks.size(); ++j) {
			double angle1 = peaks[j].x*interval;
			double a1 = cos(angle1), b1 = sin(angle1), c1 = -peaks[j].y;
			if (peaks[j].x == 90|| peaks[j].x == 270)
				a1 = 0;
			double D = a0 * b1 - a1*b0;
			//cout << "D " << D <<" "<< a0 * b1 << " " << a1 * b0 << endl;
			if (D != 0) {
				int x = (b0*c1 - b1 * c0) / D;
				int y = (a1*c0 - a0 * c1) / D;
				//cout <<"P"<< (b0*c1 - b1 * c0) / D << endl;
				if (x > 0 && x < width - 1 && y>0 && y < height - 1) {
					
					points.push_back(Point(x, y));
				}
			}
		}
	}

	cout << "Points:" << endl;

	for (auto c : points) {
		const double color[] = { 255,0,0 };
		cout << "( " << c.x << " , " << c.y << " )" << endl;
		result.draw_circle(c.x, c.y, 20, color);
	}
}


void Hough::houghCircleTransform()
{
	int max;
	vector<Point> voteSet;
	for (int r = minR; r < maxR; r++) {
		max = 0;
		houghImage = CImg<int>(width, height, 1, 1, 0);
		cimg_forXY(gradnum, x, y) {
			int value = gradnum(x, y);
			if (value != 0) {
				for (int i = 0; i < theta; i++) {
					//x0 y0ΪԲ��
					int x0 = x - r * cos(i*interval);
					int y0 = y - r * sin(i*interval);
					/*����votingͶƱ*/
					if (x0 > 0 && x0 < width && y0 > 0 && y0 < height) {
						houghImage(x0, y0)++;
					}
				}
			}
		}
		/*ÿ�α�����r���ҵ�hough��������ͶƱ�������ͶƱ����ʾ��ǰr���Ǻϳ̶ȣ�Ȼ����ͶƱ������r��Ϊ��õ�r*/
		cimg_forXY(houghImage, x, y) {
			if (houghImage(x, y) > max) {
				max = houghImage(x, y);
			}
		}
		if (max > rLimit) {
			voteSet.push_back(Point(max, r));
			//cout << max << " " << r << endl;
		}
	}

	sort(voteSet.begin(), voteSet.end(), [](const Point& a, const Point& b) -> bool {
		return a.x > b.x;
	});

	for (int i = 0; i < voteSet.size(); i++) {
		houghImage = CImg<int>(width, height, 1, 1, 0);
		cimg_forXY(gradnum, x, y) {
			int value = gradnum(x, y);
			if (value != 0) {
				for (int j = 0; j < theta; j++) {
					int x0 = x - voteSet[i].y * cos(j*interval);
					int y0 = y - voteSet[i].y * sin(j*interval);
					/*����votingͶƱ*/
					if (x0 > 0 && x0 < width && y0 > 0 && y0 < height) {
						houghImage(x0, y0)++;
					}
				}
			}
		}
		houghCirclesDetect();
		drawCircle(voteSet[i].y);
	}
	cout << "Բ�ĸ���Ϊ��" << center.size() << endl;
}

void Hough::houghCirclesDetect()
{
	/*������ͼ�������в�Ϊ0�ĵ��ӦԲ�ĵ������������*/
	cimg_forXY(houghImage, x, y) {
		if (houghImage(x, y) > voteLimit) {
			circles.push_back(Point(x, y));
			circleWeight.push_back(houghImage(x, y));
		}
	}
	//cout << circles.size() << endl;
}


void Hough::drawCircle(int r)
{
	int count = 0;
	unsigned char blue[3] = { 0, 0, 255 };
	unsigned char red[3] = { 255, 0, 0 };

	auto sortCircleWeight = circleWeight;
	sort(sortCircleWeight.begin(), sortCircleWeight.end(), greater<int>()); // ���ۼӾ���Ӵ�С��������

	while (1) {

		if (count >= sortCircleWeight.size())
			break;

		int weight = sortCircleWeight[count], index;
		vector<int>::iterator iter = find(circleWeight.begin(), circleWeight.end(), weight);
		index = iter - circleWeight.begin();
		int a = circles[index].x, b = circles[index].y;
		count++;
		//cout << "count: " << count << endl;

		int i;
		for (i = 0; i < center.size(); i++) {
			if (distance(center[i].x - a, center[i].y - b) < minRadius) {
				break; // �жϼ�������Բ�������Ƿ���Ѽ���Բ������ľ��룬��������С��Ĭ����ͬ��Բ
			}
		}
		if (i == center.size()) {
			center.push_back(Point(a, b));
			cout << "Բ�İ뾶Ϊ��" << r << endl;
			cout << "Բ������Ϊ��"<< a << " " << b << endl;
			result.draw_circle(a, b, r, blue, 5.0f, 1);
			result.draw_circle(a, b, 5, red);
			break;
		}
	}
}