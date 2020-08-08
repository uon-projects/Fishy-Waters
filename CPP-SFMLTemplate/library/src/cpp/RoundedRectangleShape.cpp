/*
 * Copyright (c) 2020 Teodor G. (TeodorHMX1)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 **/

// Created by TeodorHMX1 on 19/03/2020.

#include "../header/RoundedRectangleShape.h"
#include <cmath>

RoundedRectangleShape::~RoundedRectangleShape()
{

}

RoundedRectangleShape::RoundedRectangleShape(const Vector2f &size, float radius, unsigned int cornerPointCount)
{
    mySize = size;
    myRadius = radius;
    myCornerPointCount = cornerPointCount;
    update();
}

void RoundedRectangleShape::setSize(const Vector2f &size)
{
    mySize = size;
    update();
}

const Vector2f &RoundedRectangleShape::getSize() const
{
    return mySize;
}

void RoundedRectangleShape::setCornersRadius(float radius)
{
    myRadius = radius;
    update();
}

float RoundedRectangleShape::getCornersRadius() const
{
    return myRadius;
}

void RoundedRectangleShape::setCornerPointCount(unsigned int count)
{
    myCornerPointCount = count;
    update();
}

std::size_t RoundedRectangleShape::getPointCount() const
{
    return myCornerPointCount * 4;
}

Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
{
    if (index >= myCornerPointCount * 4)
        return Vector2f(0, 0);

    float deltaAngle = 90.0f / (myCornerPointCount - 1);
    Vector2f center;
    unsigned int centerIndex = index / myCornerPointCount;
    static const float pi = 3.141592654f;

    switch (centerIndex)
    {
        case 0:
            center.x = mySize.x - myRadius;
            center.y = myRadius;
            break;
        case 1:
            center.x = myRadius;
            center.y = myRadius;
            break;
        case 2:
            center.x = myRadius;
            center.y = mySize.y - myRadius;
            break;
        case 3:
            center.x = mySize.x - myRadius;
            center.y = mySize.y - myRadius;
            break;
    }

    return Vector2f(myRadius * cos(deltaAngle * (index - centerIndex) * pi / 180) + center.x,
                    -myRadius * sin(deltaAngle * (index - centerIndex) * pi / 180) + center.y);
}
