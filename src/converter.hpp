#pragma once

#include "glm/mat3x3.hpp"

#include <armadillo>

#include "object.hpp"

class Converter{
  public:
    static arma::vec get_velocity(const Object::State &o1, const Object::State &o2);
    static arma::mat get_invmass(const Object::State &o1, const Object::State &o2);
    static void get_velocity(arma::vec velocity, glm::dvec3 &v1, glm::dvec3 &a1, glm::dvec3 &v2, glm::dvec3 &a2);
};
