#pragma once

#include <list>

#include "cube.hpp"
#include "shape.hpp"

class CubeShape : public Shape{
  public:
    Cube *cube;
    CubeShape(Cube *c);

    bool intersectVisit(Shape *other, std::list<Contact> &contact);

    bool intersect(CubeShape *s, std::list<Contact> &contact);

    bool intersect(PlanShape *s, std::list<Contact> &contact);
};
