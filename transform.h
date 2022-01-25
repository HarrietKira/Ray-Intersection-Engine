#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "globalincludes.h"

class Transform
{
public:
    Vector3f m_translation; // store translational XYZ
    Vector3f m_scale;
    Vector3f m_rotation; // represent its Euler angles of rotation
    glm::mat4 m_worldTransform; // translate(tx,ty,tz) * rotate(rx, x_axis)*
                                // rotate(ry, y_axis) * rotate(rz, z_axis) *
                                // scale(sx, sy, sz)
    glm::mat4 m_worldTransformInverse; // inverse of the world transform matrix
    glm::mat3 m_worldTransformInverseTranspose; // transpose of the inverse of world matrix
                                                // transform surface normals from
                                                // local object space into world space
public:
    Transform();
    Transform(Vector3f t, Vector3f r, Vector3f s);
    void updateTransformMatrix(); // call in constructor
};

#endif // TRANSFORM_H
