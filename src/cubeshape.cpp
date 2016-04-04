#include "cubeshape.hpp"
#include "collisionengine.hpp"

CubeShape::CubeShape(Cube *c){
  this->cube = c;
}

bool CubeShape::intersectVisit(Shape *other, std::list<Contact> &contact){
  return other->intersect(this, contact);
}

bool CubeShape::intersect(CubeShape *s, std::list<Contact> &contact){
  return CollisionEngine::test_collide(this, s, contact);
}

bool CubeShape::intersect(PlanShape *s, std::list<Contact> &contact){
  return CollisionEngine::test_collide(this, s, contact);
}
