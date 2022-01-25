#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "ray.h"
#include "primitive.h"

class Primitive;

class Intersection
{
public:
    Point3f m_point; // intersection point on surface
    Normal3f m_normal; // surface normal at intersection point
    float m_t; // distance along the Ray at which this point of intersection lies
    const Primitive *m_objectHit; // A pointer to the Primitive
                                // whose surface we are intersecting
public:
    Intersection();
    Intersection(Point3f point, Normal3f normal, float t, const Primitive* objectHit);
};

#endif // INTERSECTION_H
