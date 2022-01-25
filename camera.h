#ifndef CAMERA_H
#define CAMERA_H

# include "ray.h"

class Camera
{
public:
    Point3f m_eye;
    Point3f m_ref; // center point of screen
    Vector3f m_worldUp;
    float m_fov; // angle of view in y dir
    float m_nearClip;
    float m_farClip;
    int m_pixelW;
    int m_pixelH;
    // calculated
    float m_width; // actual height & width
    float m_height;
    Vector3f m_widthDir; // from left to right dir
    Vector3f m_heightDir; // from top to bottom dir
    Point3f m_topLeft;
public:
    Camera();
    Camera(Point3f eye, Point3f ref, Vector3f worldUp, float fov,
           float nearClip, float farClip, int pixelW, int pixelH);
    glm::mat4 getViewMatrix();
    glm::mat4 getIViewMatrix();
    Ray rayCast(int pixelX, int pixelY);
};

#endif // CAMERA_H
