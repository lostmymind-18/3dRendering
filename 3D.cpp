#include<iostream>
#include<vector>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;

#define pi 3.14159265358979323846


int WIDTH = 120, HEIGHT = 60;


struct Point
{
    int x, y, z;
};

struct Cube{
    vector<Point> Points;
    Cube()
    {
        Points.push_back({55,55,75});
        Points.push_back({55,55,5});
        Points.push_back({55,5,75});
        Points.push_back({55,5,5});
        Points.push_back({5,55,75});
        Points.push_back({5,55,5});
        Points.push_back({5,5,75});
        Points.push_back({5,5,5});
    }
    void project(float a)
    {
        for(auto p:this->Points)
        {
            p.x = p.x + p.z*tan(a/2);
            p.y = p.y - p.z*tan(a/2);
        }
    }
};

int main()
{
    Cube cube;
    float a = pi;
    cube.project(a);
    for(auto p:cube.Points)
        cout<<p.x<<"    "<<p.y<<"   "<<p.z<<endl;
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            bool a =false;
            for(auto point:cube.Points)
            {
                if(i == point.y  && j == point.x )
                {
                    cout<<"#";
                    a = true;
                } 
            }
            if(!a)
                cout<<" ";
        }
        cout<<endl;
    }
}
