#pragma once

#include <list>

#include "shape.hpp"
#include "plan.hpp"

class PlanShape : public Shape{
  public:
    Plan *plan;
    PlanShape(Plan *p);

    bool intersectVisit(Shape *other, std::list<Contact> &contact);
    bool intersect(CubeShape *s, std::list<Contact> &contact);
    bool intersect(PlanShape *s, std::list<Contact> &contact);
};
