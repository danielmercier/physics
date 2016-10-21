#include "distancepointconstraint.hpp"

#include <cmath>

DistancePointConstraint::DistancePointConstraint(
        Object &o,
        glm::dvec3 point,
        const glm::dvec3 &r){

  this->object = &o;
  this->point = point;
  this->r = r;
  setBiasFactor(0.05);

  invmass = Converter::get_invmass(o.getState());
}

bool DistancePointConstraint::update(){
  glm::dvec3 point1 = object->toWorld(r);
  glm::dvec3 point2 = point;

  glm::dvec3 dist = point2 - point1;
  glm::dvec3 rcross = glm::cross(object->getPosition() - point1 , dist);
  setBias(glm::length(dist));

  jacobian = arma::rowvec({ -dist.x, -dist.y, -dist.z,
                rcross.x, rcross.y, rcross.z });

  Object::State st = object->getState();

  velocity = Converter::get_velocity(st);

  return true;
}

void DistancePointConstraint::apply(arma::mat lambda){
  glm::dvec3 v;
  glm::dvec3 a;


  arma::mat vec = getVelocities(lambda);

  Converter::get_velocity(vec, v, a);

  object->setLinearVelocity(v);
  object->setAngularVelocity(a);
}
