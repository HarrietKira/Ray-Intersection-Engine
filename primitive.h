#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "shape.h"

class Shape;
class Intersection;

class Primitive
{
public:
    QString m_name;
    uPtr<Shape> m_shape;
public:
    Primitive();
    std::optional<Intersection> getIntersection(Ray ray) const;
};

#endif // PRIMITIVE_H
