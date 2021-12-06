#ifndef RENDER_h
#define RENDER_h
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
#define pi 3.141
class Render
{

	int WIDTH = 60, HEIGHT = 50;

	struct Point
	{
		int x, y, z;
		bool operator!=(const Point &p)
		{
			return (this->x == p.x && this->y == p.y && this->z == p.z) ? false : true;
		}
	};

	struct Plane
	{
		Point p1, p2, p3;
		// return true if plane has a point on a determined position
		bool position(int i, int j)
		{
			vector<Point> points;
			points.push_back(p1);
			points.push_back(p2);
			points.push_back(p3);
			for (auto p : points)
			{
				if (p.x == j && p.y == i)
					return true;
				/*for (auto point : points)
				{
					for (auto p : points)
					{
						if (p != point && (j - p.x) * (j - point.x) <= 0 && (i - p.y) * (i - point.y) <= 0)
						{
							if (j == p.x && j == point.x)
								return true;
							else if(p != point && j != point.x && i != point.y &&
							abs((float)(j - p.x)/(j - point.x) - (float)(i - p.y)/(i - point.y)) ==0 )
							    return true;

							else if (i == p.y && i == point.y)
								return true;
						}
					}
				}*/
			}
			return false;
		}
	};

	struct Cube
	{
		vector<Plane> Planes;
		Cube()
		{
			// UP
			Planes.push_back({{5, 5, 5}, {5, 5, 35}, {35, 5, 5}});
			Planes.push_back({{5, 5, 35}, {35, 5, 35}, {35, 5, 5}});
			// DOWN
			Planes.push_back({{5, 35, 5}, {5, 35, 35}, {35, 35, 5}});
			Planes.push_back({{5, 35, 35}, {35, 35, 35}, {35, 35, 5}});
			// FRONT
			Planes.push_back({{5, 35, 5}, {5, 5, 5}, {35, 35, 5}});
			Planes.push_back({{5, 5, 5}, {35, 35, 5}, {35, 5, 5}});
			// BACK
			Planes.push_back({{5, 5, 35}, {35, 5, 35}, {35, 35, 35}});
			Planes.push_back({{35, 5, 35}, {35, 35, 35}, {5, 35, 35}});
			// LEFT
			Planes.push_back({{5, 5, 5}, {5, 5, 35}, {5, 35, 5}});
			Planes.push_back({{5, 5, 35}, {5, 35, 5}, {5, 35, 35}});
			// RIGHT
			Planes.push_back({{35, 5, 5}, {35, 5, 35}, {35, 35, 5}});
			Planes.push_back({{35, 5, 35}, {35, 35, 5}, {35, 35, 35}});
		}
		void project(int eye_x, int eye_y, int eye_z)
		{
			for (auto &plane : Planes)
			{
				vector<Point *> points;
				points.push_back(&plane.p1);
				points.push_back(&plane.p2);
				points.push_back(&plane.p3);
				for (auto &p : points)
				{
					if (p->z != 0)
					{
						float r = (float)eye_z / p->z;
						p->x = (p->x < eye_x) ? eye_x - (eye_x - p->x) / (1 + r) : eye_x + (p->x - eye_x) / (1 + r);
						p->y = (p->y < eye_y) ? eye_y - (eye_y - p->y) / (1 + r) : eye_y + (p->y - eye_y) / (1 + r);
					}
				}
			}
		}

		void rotX(float a)
		{
			for (auto &plane : Planes)
			{
				vector<Point *> points;
				points.push_back(&plane.p1);
				points.push_back(&plane.p2);
				points.push_back(&plane.p3);
				for (auto &p : points)
				{
					p->y = cos(a) * p->y - sin(a) * p->z;
					p->z = sin(a) * p->y + cos(a) * p->z;
				}
			}
		}

		void rotY(float a)
		{
			for (auto &plane : Planes)
			{
				vector<Point *> points;
				points.push_back(&plane.p1);
				points.push_back(&plane.p2);
				points.push_back(&plane.p3);
				for (auto &p : points)
				{
					p->x = cos(a) * (p->x-30) + sin(a) * (p->z - 30) + 30;
					p->z = -sin(a) * (p->x-30) + cos(a) * (p->z-30) + 30;
				}
			}
		}
	};

public:
	void draw()
	{
		Cube cube;
		Cube origin;
		int eye_x = 20;
		int eye_y = 20;
		int eye_z = 20;
		float a = 0.0;
		while(true)
		{
			cube.rotY(a);
			cube.project(eye_x, eye_y, eye_z);
			for (int i = 0; i < HEIGHT; i++)
			{
				for (int j = 0; j < WIDTH; j++)
				{
					for (auto plane : cube.Planes)
					{
						if (plane.position(i, j))
						{
							cout << ".";
							goto nextPosition;
						}
					}
					cout << " ";
					
				nextPosition:
					continue;
					/*if(i == 0 || j  == 0 || i == HEIGHT - 1 || j == WIDTH - 1)
						cout<<"#";
					else cout<<" ";*/
				}
				cout << endl;
			}
			usleep(pow(10,5));
			system("clear");
			cube = origin;
			a += 0.1;
			if (a > 2 * pi)
				a -= 2 * pi;
		}
	}
};

#endif
