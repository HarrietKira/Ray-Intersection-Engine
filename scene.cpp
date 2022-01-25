#include "scene.h"

Scene::Scene(){}

Scene::Scene(Camera camera)
    : m_camera(camera)
{}

bool Scene::getIntersection(Ray ray, Intersection* intersection) const
{
    bool hasIntersection = false;
    float currT = FLT_MAX;
    for(auto& p : m_primitiveVector)
    {
        Primitive* currP = p.get();
        auto intersectionRes = currP->getIntersection(ray);
        if(intersectionRes != std::nullopt) // intersects
        {
            hasIntersection = true;
            if(intersectionRes->m_t < currT)
            {
                intersection->m_point = intersectionRes->m_point;
                intersection->m_normal = intersectionRes->m_normal;
                intersection->m_t = intersectionRes->m_t;
                intersection->m_objectHit = intersectionRes->m_objectHit;
                currT = intersectionRes->m_t;
            }
        }
    }
    return hasIntersection;
}
