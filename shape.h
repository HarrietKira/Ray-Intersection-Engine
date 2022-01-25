#ifndef SHAPE_H
#define SHAPE_H

#include "transform.h"
#include "intersection.h"

class Intersection;
class Shape
{
public:
    Transform m_transform;
public:
    Shape();
    Shape(Transform transform);
    virtual ~Shape();
    virtual std::optional<Intersection> getIntersection(Ray) const=0;
};

#endif // SHAPE_H
