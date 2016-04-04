#pragma once

#include <list>

#include "contact.hpp"

class CubeShape;
class PlanShape;

class Shape{
  public:
    virtual bool intersectVisit(Shape *other, std::list<Contact> &) = 0;
    virtual bool intersect(CubeShape *, std::list<Contact> &) = 0;
    virtual bool intersect(PlanShape *, std::list<Contact> &) = 0;
};
