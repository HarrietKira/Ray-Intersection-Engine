#pragma once

#include <memory>
#include <include/glm/glm.hpp>
#include <include/glm/gtc/matrix_transform.hpp>
#include <vector>
#include <assert.h>
#include <string.h>
#include <QString>
#include <optional>
#include <qdebug.h>

typedef glm::vec3 Color3f;
typedef glm::vec3 Point3f;
typedef glm::vec3 Normal3f;
typedef glm::vec2 Point2f;
typedef glm::ivec2 Point2i;
typedef glm::ivec3 Point3i;
typedef glm::vec3 Vector3f;
typedef glm::vec2 Vector2f;
typedef glm::ivec2 Vector2i;

#define mkU std::make_unique
#define mkS std::make_shared
#define uPtr std::unique_ptr
#define sPtr std::shared_ptr

#define Opt std::optional
