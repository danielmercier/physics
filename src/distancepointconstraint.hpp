#pragma once

#include "constraint.hpp"
#include "object.hpp"
#include "converter.hpp"

class DistancePointConstraint : public Constraint{
  private:
    Object *object;
    glm::dvec3 point;
    glm::dvec3 r;

  protected:
    virtual bool update();

  public:
    DistancePointConstraint(
        Object &o,
        glm::dvec3 point,
        const glm::dvec3 &r = glm::dvec3(0., 0., 0.));

    virtual void apply(arma::mat lambda);
};
