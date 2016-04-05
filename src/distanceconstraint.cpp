#include "distanceconstraint.hpp"

#include "converter.hpp"

DistanceConstraint::DistanceConstraint(const Object::State &o1, const Object::State &o2){
  glm::dvec3 absolute = glm::dvec3(o1.bodyToWorld * glm::dvec4(0., 0., 0., 1.));
  glm::dvec3 dist = o2.position - absolute;
  glm::dvec3 r1cross = glm::cross(o1.position - absolute , dist);
  glm::dvec3 r2cross = glm::cross(glm::dvec3(0., 0., 0.), dist);
  jacobian = arma::rowvec({ -dist.x, -dist.y, -dist.z,
                //r1cross.x, r1cross.y, r1cross.z,
                0, 0, 0,
                dist.x, dist.y, dist.z,
                //r2cross.x, r2cross.y, r2cross.z });
                0, 0, 0 });
  velocity = Converter::get_velocity(o1, o2);
  invmass = Converter::get_invmass(o1, o2);
  bias = 0.1;
}
