#include "cube.hpp"
#include "cubeshape.hpp"

#define CARRE(x) x * x

Cube::Cube(double mass, glm::dvec3 scaling){
  _collisionShape = new CubeShape(this);
  this->scaling = scaling;

  vertices.push_back(scaling * glm::dvec3(-1., 1., 1.));
  vertices.push_back(scaling * glm::dvec3(-1., 1., -1.));
  vertices.push_back(scaling * glm::dvec3(1., 1., -1.));
  vertices.push_back(scaling * glm::dvec3(1., 1., 1.));

  vertices.push_back(scaling * glm::dvec3(-1., -1., 1.));
  vertices.push_back(scaling * glm::dvec3(-1., -1., -1.));
  vertices.push_back(scaling * glm::dvec3(1., -1., -1.));
  vertices.push_back(scaling * glm::dvec3(1., -1., 1.));

  // matrice d'inertie pour un parallélépipède
  current.inertiaTensor =
        { { CARRE(scaling.y) + CARRE(scaling.z), 0                            , 0                             },
          { 0                            , CARRE(scaling.x) + CARRE(scaling.z), 0                             },
          { 0                            , 0                            , CARRE(scaling.x) + CARRE(scaling.y) }
        };

  current.inertiaTensor = (mass / 12.) * current.inertiaTensor;
  current.mass = mass;

  current.inverseInertiaTensor = glm::inverse(current.inertiaTensor);
  current.inverseMass = 1. / mass;
}
