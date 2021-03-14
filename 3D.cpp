#include<iostream>
#include<vector>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
using namespace std;

struct Point{
    float x, y ,z;
    Point(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

class Geo{
    public:
    vector<Point> points;
    float a = 0.0f;
    void rotaX(vector<Point>& copy)
    {
        if(a>6.283185307) a -= 6.283185307;
        a+=0.1;
        for(auto& point:copy)
        {
            float x = point.x, y = point.y, z = point.z;
            point.y = cos(a)*y - sin(a)*z;
            point.z = sin(a)*y + cos(a)*z;
        }
    }
    void rotaSepecial(vector<Point>& copy)
    {
        if(a>6.283185307) a -= 6.283185307;
        a+=0.1;
        for(auto& point:copy)
        {
            float x = point.x, y = point.y, z = point.z;
            point.x = cos(a)*y - sin(a)*z;
            point.y = cos(a)*x - sin(a)*z;
            point.z = -sin(a)*x + cos(a)*z;
        }
    }
    void rotaZ(vector<Point>& copy)
    {
        if(a>6.283185307) a -= 6.283185307;
        a+=0.1;
        for(auto& point:copy)
        {
            float x = point.x, y = point.y, z = point.z;
            point.x = cos(a)*x - sin(a)*y;
            point.y = sin(a)*x + cos(a)*y;
        }
    }
    void rotaXY(vector<Point>& copy)
    {
        if(a>6.283185307) a -= 6.283185307;
        a+=0.1;
        for(auto& point:copy)
        {
            float x = point.x, y = point.y, z = point.z;
            point.x = cos(a)*x - sin(a)*y;
            point.y = sin(a)*x + cos(a)*y;
        }
    }
};
class Cube:public Geo{
    public:
    Cube()
    {
        points ={
            {15.0f, 15.0f, 15.0f},
            {15.0f, -15.0f, 15.0f},
            {-15.0f, 15.0f, 15.0f},
            {-15.0f, -15.0f, 15.0f},
            {15.0f, 15.0f, -15.0f},
            {15.0f, -15.0f, -15.0f},
            {-15.0f, 15.0f, -15.0f},
            {-15.0f, -15.0f, -15.0f}
        };
        vector<Point> match;
        for(auto point:points)
        {
            if(point.x < 0)
            {
                for(int i = point.x+1; i < -point.x; i++)
                match.push_back({i, point.y, point.z});
            }
            if(point.y < 0)
            {
                for(int i = point.y+1; i < -point.y; i++)
                match.push_back({point.x, i, point.z});
            }
            if(point.z < 0)
            {
                for(int i = point.z+1; i < -point.z; i++)
                match.push_back({point.x, point.y, i});
            }
        }      
        points.insert(end(points), begin(match), end(match));
    }
};
void draw(int x, int y, vector<Point> copy)
{
        for(int j = 0; j < y; j++)
        {
            for(int i = 0; i < x; i++)
            {
                bool a = false;
                if(i == 26 && j == 24)
                {
                    cout<<".";
                }
                else
                {
                    for(auto point:copy)
                    {
                       if(i == (int)(point.x+25) && j == (int)(point.y+25))
                       {
                           cout<<".";
                           a = true;
                           break;
                       }
                    }
                    if(!a) cout<<" ";
                }
            }
            cout<<endl;
        }
}
int main()
{
    Cube cub;
    vector<Point> copy = cub.points;
    char c = 'a';
    while(1)
    {
    draw(70, 50, copy);
    usleep(pow(10,5));
    system("clear");
    copy = cub.points;
    cub.rotaSepecial(copy);
    //cin>>c;
    }
}