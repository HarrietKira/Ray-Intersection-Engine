#include "ray.h"

Ray::Ray(Point3f origin, Vector3f dir)
    : m_origin(origin),
      m_dir(dir)
{}

Ray Ray::Transform(glm::mat4 m)
{
    glm::vec4 origin4 = glm::vec4(m_origin, 1.f);
    glm::vec4 dir4 = glm::vec4(m_dir, 0.f);
    glm::vec4 trans_origin4 = m * origin4;
    glm::vec4 trans_dir4 = m * dir4;
    Ray res = Ray(Point3f(trans_origin4.x, trans_origin4.y, trans_origin4.z),
                  Vector3f(trans_dir4.x, trans_dir4.y, trans_dir4.z));
    return res;
}
