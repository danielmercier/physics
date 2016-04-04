#pragma once

#include <vector>
#include <algorithm>

#include "collisionengine.hpp"
#include "object.hpp"
#include "contact.hpp"
#include "constraint.hpp"

class PhysicsEngine{
  private:
    std::vector<Object*> objects;

  public:
    void add(Object *o);

    void update(double t, double dt);

    double get_impulse(const Object::State &obj1, const Object::State &obj2, const Contact &c);
    void apply_impulse(Object::State &obj1, Object::State &obj2, const Contact &c, double j);
    double apply_friction(Object::State &obj, double t, const Contact &c, double jr);
};
