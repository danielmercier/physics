#pragma once

#include "object.hpp"

class Cube : public Object{
  public:
    /*mise a l'échelle de l'objet*/
    glm::dvec3 scaling;

    /*Constructeur de base qui initialise le cube*/
    Cube(double mass = 1., glm::dvec3 scaling = glm::dvec3(1., 1., 1.));
};
