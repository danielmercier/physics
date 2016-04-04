#pragma once

#include "glm/vec3.hpp"
#include "glm/gtx/intersect.hpp"

#include "shape.hpp"

class CollisionEngine{
  public:
    static bool test_collide(PlanShape *cube, CubeShape *plan, std::list<Contact> &contact);
    static bool test_collide(CubeShape *cube1, CubeShape *cube2, std::list<Contact> &contact);
    static bool test_collide(PlanShape *plan1, PlanShape *plan2, std::list<Contact> &contact);
    static bool test_collide(CubeShape *cube, PlanShape *plan, std::list<Contact> &contact);
};
