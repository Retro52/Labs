//
// Created by Anton on 14.12.2021.
//

#ifndef GRAPHICS_STRUCTURES_H
#define GRAPHICS_STRUCTURES_H
#include <iostream>
#include "../OpenGL/include/glm/glm.hpp"

struct Float3
{
    float Data [3];
    void display(const std::string& name)
    {
        std::cout << name << " data:" << std::endl;
        for(int i = 0; i < 3; i++)
        {
            std::cout << Data[i] << "; ";
        }
        std::cout << std::endl;
    }
};

struct Face
{
    int vertex [3] [3];
    void display()
    {
        std::cout << "Face" << std::endl;
        for(int i = 0; i < 3; i++)
        {
            std::cout << "Coords: ";
            for(int j = 0; j < 3; j++)
            {
                std::cout << " " << vertex[i][j] << " ; ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

class List
{
public:
    List() :mNext(nullptr) {}
    void * mNext;
    template<typename T>
    T * Next ()
    {
        return(T*) mNext;
    }

    void PushBack(List* node)
    {
        List * mNode = this;
        while (mNode->mNext != nullptr)
        {
            mNode = mNode->Next<List>();
        }
        mNode->mNext = node;
    }
};

struct Point
{
    float x, y;

    Point() : x(0), y(0) {};
    Point(float s) : x(s), y(s) {};
    Point(float x, float y) : x(x), y(y) {};

    Point operator+(const Point &point)
    {
        return {x + point.x, y + point.y };
    }

    Point operator-(const Point &point)
    {
        return {x - point.x, y - point.y };
    }

    Point operator-() const
    {
        return {-x, -y };
    }

    Point operator*(const Point &point)
    {
        return {x * point.x, y * point.y };
    }

    Point operator*(const float scalar)
    {
        return {x * scalar, y * scalar };
    }

    Point operator/(const Point &point) const
    {
        return {x / point.x, y / point.y };
    }

    Point operator/(const float scalar)
    {
        return {x / scalar, y / scalar };
    }

    Point operator+=(const Point &b)
    {
        x += b.x;
        y += b.y;
        return {x, y };
    }

    Point operator-=(const Point &b)
    {
        x -= b.x;
        y -= b.y;
        return {x, y };
    }

    Point operator/=(const Point &b)
    {
        x /= b.x;
        y /= b.y;
        return {x, y };
    }

    Point operator*=(const Point &b)
    {
        x *= b.x;
        y *= b.y;
        return {x, y };
    }

    bool operator>(const Point &b) const
    {
        return x > b.x && y > b.y;
    }

    bool operator>=(const Point &b) const
    {
        return x >= b.x && y >= b.y;
    }

    bool operator<(const Point &b) const
    {
        return x < b.x && y < b.y;
    }

    bool operator<=(const Point &b) const
    {
        return x <= b.x && y <= b.y;
    }
};
#endif //GRAPHICS_STRUCTURES_H
