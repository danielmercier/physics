#include "plan.hpp"
#include "planshape.hpp"

Plan::Plan(glm::dvec3 origin, glm::dvec3 normal){
  _collisionShape = new PlanShape(this);
  this->normal = glm::normalize(normal);
  this->origin = origin;
}
