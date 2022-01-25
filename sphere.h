#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class Sphere : public Shape
{
public:
    Point3f m_origin;
    float m_radius;
public:
    Sphere();
    virtual Opt<Intersection> getIntersection(Ray ray) const;
    ~Sphere();
};

#endif // SPHERE_H
