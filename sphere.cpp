#include "sphere.h"

Sphere::Sphere()
    : m_origin(Point3f(0.f, 0.f, 0.f)),
      m_radius(0.5f)
{}

Sphere::~Sphere(){}

Opt<Intersection> Sphere::getIntersection(Ray ray) const
{
    Ray localRay = ray.Transform(m_transform.m_worldTransformInverse);
    Point3f Rd = localRay.m_dir;
    Vector3f Ro = localRay.m_origin;
    float A = glm::dot(Rd, Rd);
    float B = 2 * glm::dot(Rd, Ro - m_origin);
    float C = glm::dot(m_origin - Ro, m_origin - Ro) - m_radius * m_radius;
    float delta = B * B - 4 * A * C;
    if (delta >= 0)
    {
        float t0 = (-1.f * B - pow(delta, 0.5)) / (2.f * A);
        float t1 = (-1.f * B + pow(delta, 0.5)) / (2.f * A);

        float t = 0;
        if (t0 < 0 && t1 < 0) return std::nullopt;
        if (t0 < 0)  t = t1;
        else t = t0;
        Intersection res;
        res.m_t = t;
        res.m_point = Ro + t * Rd;
        res.m_normal = glm::normalize(m_transform.m_worldTransformInverseTranspose *
                                      (res.m_point-m_origin));
        return Opt<Intersection>(res);
    }
    return std::nullopt;
}
