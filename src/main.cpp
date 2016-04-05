#include "cube.hpp"
#include "cuberenderer.hpp"
#include "openglscene.hpp"

int main (int argc, char **argv) {
  Engine e;

  Cube c(10., glm::dvec3(1., 1., 1.));
  CubeRenderer cr(c);
  c.setPosition(glm::dvec3(0., 10., 0.));
  c.setLinearVelocity(glm::dvec3(0., 0., 0.));
  e.add(c, cr);

  Cube c2(10., glm::dvec3(1., 1., 1.));
  CubeRenderer cr2(c2);
  c2.setPosition(glm::dvec3(0., 8., 0.));
  c2.setLinearVelocity(glm::dvec3(0., 0., 0.));
  e.add(c2, cr2);

  //Cube c2(100., glm::dvec3(4., 4., 4.));
  //CubeRenderer cr2(c2);
  //c2.setPosition(glm::dvec3(5., 20., 0.));
  //e.add(c2, cr2);

  Plan p(glm::dvec3(0., 0., 0.), glm::dvec3(0., 1., 0.));
  PlanRenderer pr(p);
  e.add(p, pr);

  call_gl(argc, argv, e);

  return 0;
}
