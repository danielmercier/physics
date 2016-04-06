#pragma once

#include "object.hpp"
#include "constraint.hpp"

class DistanceConstraint : public Constraint{
  private:
    Object *object1;
    Object *object2;
    glm::dvec3 r1;
    glm::dvec3 r2;

  protected:
    virtual bool update();

  public:
    DistanceConstraint(
        Object &o1,
        Object &o2,
        const glm::dvec3 &r1 = glm::dvec3(0., 0., 0.),
        const glm::dvec3 &r2 = glm::dvec3(0., 0., 0.));

    virtual void apply(arma::mat lambda);
};
