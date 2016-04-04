#include "planshape.hpp"
#include "collisionengine.hpp"

PlanShape::PlanShape(Plan *p){
  this->plan = p;
}

bool PlanShape::intersectVisit(Shape *other, std::list<Contact> &contact){
  return other->intersect(this, contact);
}

bool PlanShape::intersect(CubeShape *s, std::list<Contact> &contact){
  return CollisionEngine::test_collide(this, s, contact);
}

bool PlanShape::intersect(PlanShape *s, std::list<Contact> &contact){
  return CollisionEngine::test_collide(this, s, contact);
}
