//
// Created by Anton on 15.08.2022.
//

#ifndef GRAPHICS_UIBASE_H
#define GRAPHICS_UIBASE_H

#include "../Core/Structures.h"
#include <memory>

struct Bounds
{
    Point lUpperCorner, lLowerCorner, rUpperCorner, rLowerCorner;

    bool IsOverlapping(const Point &point) const
    {
        return lUpperCorner > point && point > rLowerCorner && lLowerCorner < point && point < rUpperCorner;
    }
};

class UIBase
{
private:
    Point position;
    Bounds bounds;
    std::string text;
    int fontSize = 12;

    bool isMouseOver, isMouseClicked;

    UIBase();
    UIBase(const Point &position);

    ~UIBase();
public:
    virtual void Draw() const;
    void OnMouseEntered() const;

    bool IsMouseOver();
};


#endif //GRAPHICS_UIBASE_H
