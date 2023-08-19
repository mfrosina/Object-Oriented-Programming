// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>

const char BIN_FILE_NAME[32] = "input-points.dat";

struct Point
{
	float x;
	float y;
};

unsigned findNumberOfPoints()
{
	std::ifstream in(BIN_FILE_NAME, std::ios::binary);
	if (!in.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	in.seekg(0, std::ios::end);
	unsigned n = in.tellg() / sizeof(Point);
	in.close();
	return n;
}

Point* readPoints()
{
	std::ifstream in(BIN_FILE_NAME, std::ios::binary);
	if (!in.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	unsigned size = findNumberOfPoints();
	Point* points = new Point[size];
	for (unsigned i = 0; i < size; i++)
	{
		in.read((char*)&points[i], sizeof(Point));
	}
	in.close();
	return points;
}

Point centerOfGravity(const Point* points, unsigned size)
{
	float centerX = 0, centerY = 0;
	for (unsigned i = 0; i < size; i++)
	{
		centerX += points[i].x;
		centerY += points[i].y;
	}
	centerX /= size;
	centerY /= size;

	return Point{ centerX,centerY };
}

float distanceToCenter(const Point& center, const Point& point)
{
	float dist = ((point.x - center.x) * (point.x - center.x)) + ((point.y - center.y) * (point.y - center.y));
	return sqrt(dist);
}

void swap(Point& p1, Point& p2)
{
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

void sortPointsByDistanceToCenter(Point*& points, unsigned size)
{
	Point center = centerOfGravity(points, size);
	for (unsigned i = 0; i < size; i++)
	{
		float distI = distanceToCenter(center, points[i]);
		for (unsigned j = i + 1; j < size; j++)
		{
			float distJ = distanceToCenter(center, points[j]);
			if (distI < distJ)
			{
				swap(points[i], points[j]);
			}
		}
	}
}

void printFarthestFromCenter(Point* points, unsigned size)
{
	sortPointsByDistanceToCenter(points, size);
	if (size < 3)
	{
		std::cout << "There are less than 3 points...\n";
		return;
	}
	for (unsigned i = 0; i < 3; i++)
	{
		std::cout << "(" << points[i].x << ", " << points[i].y << ")\n";
	}
}

void printContentFromBinFile(const Point* points, unsigned size)
{
	for (unsigned i = 0; i < size; i++)
	{
		std::cout << "(" << points[i].x << ", " << points[i].y << ")\n";
	}
}

void outsideTheCircle(Point*& points, unsigned size, float radius)
{
	Point center = centerOfGravity(points, size);

	for (unsigned i = 0; i < size; i++)
	{
		if ((points[i].x - center.x > radius) || (points[i].y - center.y > radius))
		{
			points[i].x = center.x;
			points[i].y = center.y;
		}
	}
	
}

void writeToFile()
{
	std::ofstream out(BIN_FILE_NAME, std::ios::binary);
	if (!out.is_open())
	{
		throw std::out_of_range("Can not open file");
	}
	Point p1{ 5.5, 6.0 };
	Point p2{ 2.0,3.3 };
	Point p3{ 10.0,3.3 };
	Point p4{ 3.0,8.3 };

	out.write((const char*)&p1, sizeof(Point));
	out.write((const char*)&p2, sizeof(Point));
	out.write((const char*)&p3, sizeof(Point));
	out.write((const char*)&p4, sizeof(Point));

	out.close();
}
int main()
{
	writeToFile();
	unsigned size = findNumberOfPoints();
	Point* points = readPoints();
	printFarthestFromCenter(points, size);
	
	delete[]points;
	return 0;
}

