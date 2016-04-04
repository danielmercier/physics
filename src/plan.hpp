#pragma once

#include "object.hpp"

class Plan : public Object{
  public:
    /*Initialise le plan*/
    Plan(glm::dvec3 origin, glm::dvec3 normal);

    glm::dvec3 normal;
    glm::dvec3 origin;
};
