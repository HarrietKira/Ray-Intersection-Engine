#ifndef SQUAREPLANE_H
#define SQUAREPLANE_H

#include "shape.h"

class SquarePlane : public Shape
{
public:
    Point3f m_origin;
    float m_sideLength;
    Vector3f m_normal;
public:
    SquarePlane();
    ~SquarePlane();
    virtual Opt<Intersection> getIntersection(Ray ray) const;
    bool insidePlane(Point3f point) const;
};

#endif // SQUAREPLANE_H
