#include "primitive.h"

Primitive::Primitive(){}

std::optional<Intersection> Primitive::getIntersection(Ray ray) const
{
    std::optional<Intersection> res = m_shape->getIntersection(ray);
    if (res != std::nullopt)
    {
        res->m_objectHit = this;
        return res;
    }
    return std::nullopt;
}
