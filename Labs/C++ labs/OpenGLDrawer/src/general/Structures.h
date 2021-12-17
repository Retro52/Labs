//
// Created by Anton on 14.12.2021.
//

#ifndef GRAPHICS_STRUCTURES_H
#define GRAPHICS_STRUCTURES_H
#include <iostream>

struct Float3
{
    float Data [3]; // Структура трех элементов float для хранения данных
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
    int vertex [3] [3]; // Три точки образуют поверхность, каждая точка имеет три индекса информации
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

class List // операция связанного списка
{
public:
    List() :mNext(nullptr) {}
    void * mNext; // Следующий узел
    template<typename T>
    T * Next () // Получить следующий узел
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

    }// Вставить узел в конец связанного списка

};

#endif //GRAPHICS_STRUCTURES_H
