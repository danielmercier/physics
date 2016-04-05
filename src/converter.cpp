#include "converter.hpp"

arma::vec Converter::get_velocity(const Object::State &o1, const Object::State &o2){
  arma::vec vel =
    { o1.velocity.x, o1.velocity.y, o1.velocity.z,
      o1.angularVelocity.x, o1.angularVelocity.y, o1.angularVelocity.z,
      o2.velocity.x, o2.velocity.y, o2.velocity.z,
      o2.angularVelocity.x, o2.angularVelocity.y, o2.angularVelocity.z };
  return vel;
}

arma::mat Converter::get_invmass(const Object::State &o1, const Object::State &o2){
  glm::mat3 I1 = o1.inverseInertiaTensor;
  glm::mat3 I2 = o2.inverseInertiaTensor;
  arma::mat invmass =
    { { o1.inverseMass, 0             , 0             , 0       , 0       , 0       , 0             , 0                 , 0             , 0      , 0       , 0        },
      { 0             , o1.inverseMass, 0             , 0       , 0       , 0       , 0             , 0                 , 0             , 0      , 0       , 0        },
      { 0             , 0             , o1.inverseMass, 0       , 0       , 0       , 0             , 0                 , 0             , 0      , 0       , 0        },
      { 0             , 0             , 0             , I1[0][0], I1[0][1], I1[0][2], 0             , 0                 , 0             , 0      , 0       , 0        },
      { 0             , 0             , 0             , I1[1][0], I1[1][1], I1[1][2], 0             , 0                 , 0             , 0      , 0       , 0        },
      { 0             , 0             , 0             , I1[2][0], I1[2][1], I1[2][2], 0             , 0                 , 0             , 0      , 0       , 0        },
      { 0             , 0             , 0             , 0       , 0       , 0       , o2.inverseMass, 0                 , 0             , 0      , 0       , 0        },
      { 0             , 0             , 0             , 0       , 0       , 0       , 0             , o2.inverseMass    , 0             , 0      , 0       , 0        },
      { 0             , 0             , 0             , 0       , 0       , 0       , 0             , 0                 , o2.inverseMass, 0      , 0       , 0        },
      { 0             , 0             , 0             , 0       , 0       , 0       , 0             , 0                 , 0             ,I2[0][0], I2[0][1], I2[0][2] },
      { 0             , 0             , 0             , 0       , 0       , 0       , 0             , 0                 , 0             ,I2[1][0], I2[1][1], I2[1][2] },
      { 0             , 0             , 0             , 0       , 0       , 0       , 0             , 0                 , 0             ,I2[2][0], I2[2][1], I2[2][2] }
    };

  return invmass;
}

static arma::mat get_invmass_only(const Object::State &o1, const Object::State &o2){

}

void Converter::get_velocity(arma::vec velocity, glm::dvec3 &v1, glm::dvec3 &a1, glm::dvec3 &v2, glm::dvec3 &a2){
  v1.x = velocity[0];
  v1.y = velocity[1];
  v1.z = velocity[2];

  a1.x = velocity[3];
  a1.y = velocity[4];
  a1.z = velocity[5];

  v2.x = velocity[6];
  v2.y = velocity[7];
  v2.z = velocity[8];

  a2.x = velocity[9];
  a2.y = velocity[10];
  a2.z = velocity[11];
}
