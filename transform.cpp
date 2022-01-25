#include "transform.h"

Transform::Transform()
    : m_translation(Vector3f(0.f)),
      m_scale(Vector3f(1.f)),
      m_rotation(Vector3f(0.f))
{
    updateTransformMatrix();
}

Transform::Transform(Vector3f t, Vector3f r, Vector3f s)
    : m_translation(t),
      m_scale(s),
      m_rotation(r)
{
    updateTransformMatrix();
}

void Transform::updateTransformMatrix()
{
    m_worldTransform = glm::translate(glm::mat4(), m_translation) *
                       glm::rotate(glm::mat4(), m_rotation.x, glm::vec3(1.f, 0.f, 0.f)) *
                       glm::rotate(glm::mat4(), m_rotation.y, glm::vec3(0.f, 1.f, 0.f)) *
                       glm::rotate(glm::mat4(), m_rotation.z, glm::vec3(0.f, 0.f, 1.f)) *
                       glm::scale(glm::mat4(), m_scale);
    m_worldTransformInverse = glm::inverse(m_worldTransform);
    m_worldTransformInverseTranspose = glm::mat3(glm::transpose(m_worldTransformInverse));
}
