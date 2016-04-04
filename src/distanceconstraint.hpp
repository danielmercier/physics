#pragma once

#include "object.hpp"
#include "constraint.hpp"

class DistanceConstraint : public Constraint{
  public:
    DistanceConstraint(const Object::State &o1, const Object::State &o2);
};
