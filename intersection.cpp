#include "intersection.h"

Intersection::Intersection(){}

Intersection::Intersection(Point3f point, Normal3f normal,
                           float t, const Primitive* objectHit)
    : m_point(point),
      m_normal(normal),
      m_t(t),
      m_objectHit(objectHit)
{}
