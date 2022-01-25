#include "squareplane.h"

SquarePlane::SquarePlane()
    : m_origin(Point3f(0.f)),
      m_sideLength(1.f),
      m_normal(Vector3f(0.f, 0.f, 1.f))
{}

SquarePlane::~SquarePlane(){}

Opt<Intersection> SquarePlane::getIntersection(Ray ray) const
{
    Ray localRay = ray.Transform(m_transform.m_worldTransformInverse);
    Point3f Rd = localRay.m_dir;
    Vector3f Ro = localRay.m_origin;
    float t = glm::dot(m_normal, (m_origin - Ro)) / glm::dot(m_normal, Rd);
    Intersection res;
    Point3f point = Ro + t * Rd;
    if (insidePlane(point))
    {
        res.m_point = Point3f(m_transform.m_worldTransformInverse *
                              glm::vec4(point.x, point.y, point.z, 1.0f));
        res.m_t = t;
        res.m_normal = glm::normalize(m_transform.m_worldTransformInverseTranspose *
                                      m_normal);
        return res;
    }
    return std::nullopt;
}

bool SquarePlane::insidePlane(Point3f point) const
{
    if (point.x >= m_origin.x - 0.5f * m_sideLength &&
        point.x <= m_origin.x + 0.5f * m_sideLength)
    {
        if (point.y >= m_origin.y - 0.5f * m_sideLength &&
            point.y <= m_origin.y + 0.5f * m_sideLength)
        {
            return true;
        }
    }
    return false;
}
