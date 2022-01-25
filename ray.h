#ifndef RAY_H
#define RAY_H

#include "globalincludes.h"

class Ray
{
public:
    Point3f m_origin;
    Vector3f m_dir;
public:
    Ray(Point3f origin, Vector3f dir);
    Ray Transform(glm::mat4 m);
};

#endif // RAY_H
