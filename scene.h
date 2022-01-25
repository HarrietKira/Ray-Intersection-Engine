#ifndef SCENE_H
#define SCENE_H

#include "primitive.h"
#include "camera.h"

class Scene
{
public:
    std::vector<uPtr<Primitive>> m_primitiveVector;
    Camera m_camera;
public:
    Scene();
    Scene(Camera camera);
    bool getIntersection(Ray ray, Intersection* intersection) const;
};

#endif // SCENE_H
