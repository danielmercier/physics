#include "distanceconstraint.hpp"

#include "converter.hpp"

DistanceConstraint::DistanceConstraint(
    Object &o1,
    Object &o2,
    const glm::dvec3 &r1,
    const glm::dvec3 &r2){

  object1 = &o1;
  object2 = &o2;

  this->r1 = r1;
  this->r2 = r2;

  invmass = Converter::get_invmass(o1.getState(), o2.getState());
}

bool DistanceConstraint::update(){
  glm::dvec3 point1 = object1->toWorld(r1);
  glm::dvec3 point2 = object2->toWorld(r2);

  glm::dvec3 dist = point2 - point1;
  glm::dvec3 r1cross = glm::cross(object1->getPosition() - point1 , dist);
  glm::dvec3 r2cross = glm::cross(point2 - object2->getPosition(), dist);

  jacobian = arma::rowvec({ -dist.x, -dist.y, -dist.z,
                r1cross.x, r1cross.y, r1cross.z,
                dist.x, dist.y, dist.z,
                r2cross.x, r2cross.y, r2cross.z });

  Object::State st1 = object1->getState();
  Object::State st2 = object2->getState();

  velocity = Converter::get_velocity(st1, st2);

  return true;
}

void DistanceConstraint::apply(arma::mat lambda){
  glm::dvec3 v1;
  glm::dvec3 a1;
  glm::dvec3 v2;
  glm::dvec3 a2;

  arma::mat vec = getVelocities(lambda[0]);

  Converter::get_velocity(vec, v1, a1, v2, a2);

  object1->setLinearVelocity(v1);
  object1->setAngularVelocity(a1);

  object2->setLinearVelocity(v2);
  object2->setAngularVelocity(a2);
}
