#include "distanceconstraint.hpp"

#include "converter.hpp"

DistanceConstraint::DistanceConstraint(const Object::State &o1, const Object::State &o2){
  glm::dvec3 dist = o2.position - o1.position;
  glm::dvec3 r1cross = glm::cross(o1.position, dist);
  glm::dvec3 r2cross = glm::cross(o2.position, dist);
  jacobian = { -dist.x, -dist.y, -dist.z,
                -r1cross.x, -r1cross.y, -r1cross.z,
                dist.x, dist.y, dist.z,
                r2cross.x, r2cross.y, r2cross.z };
  velocity = Converter::get_velocity(o1, o2);
  invmass = Converter::get_invmass(o1, o2);
  bias = 0.;
}
