#include "camera.h"

Camera::Camera(){}

Camera::Camera(Point3f eye, Point3f ref, Vector3f worldUp,
               float fov, float nearClip, float farClip,
               int pixelW, int pixelH)
    : m_eye(eye), m_ref(ref),
      m_worldUp(worldUp), m_fov(fov),
      m_nearClip(nearClip), m_farClip(farClip),
      m_pixelW(pixelW), m_pixelH(pixelH)
{
    Vector3f eye2ref = ref - eye;
    float fovRad = fov * 3.14f / 180.f;
    m_height = 2.f * (glm::length(eye2ref) * tan(fovRad / 2.f));
    m_width = m_height * (float)m_pixelW / (float)m_pixelH;
    m_heightDir = glm::normalize(-m_worldUp);
    m_widthDir = glm::normalize(glm::cross(m_heightDir, eye2ref));
    m_topLeft = m_ref - 0.5f * m_heightDir * m_height - 0.5f * m_widthDir * m_width;
}

glm::mat4 Camera::getViewMatrix()
{
    glm::mat4 res = glm::perspective(glm::radians(m_fov),
                                     (float)m_pixelW / (float)m_pixelH,
                                     m_nearClip, m_farClip) *
                                     glm::lookAt(m_eye, m_ref, m_worldUp);
    return res;
}

glm::mat4 Camera::getIViewMatrix()
{
    return glm::inverse(getViewMatrix());
}

Ray Camera::rayCast(int pixelX, int pixelY)
{
    float x = (float)pixelX * m_width / (float)m_pixelW;
    float Y = (float)pixelY * m_height / (float)m_pixelH;
    Point3f worldPoint = m_topLeft + m_heightDir * Y + m_widthDir * x;
    return Ray(m_eye, glm::normalize(worldPoint - m_eye));
}
