#pragma once

#include <vector>

#include "glm/vec3.hpp"

struct Contact{
  glm::dvec3 impact;
  glm::dvec3 normal;
  double restitution;
  double static_friction;
  double dynamic_friction;
};
