#include "cube.hpp"
#include "cuberenderer.hpp"
#include "openglscene.hpp"
#include "physicsengine.hpp"
#include "distanceconstraint.hpp"
#include "distancepointconstraint.hpp"

int main (int argc, char **argv) {
  PhysicsEngine physics;
  Engine e(physics);

  int n = 10;
  double size = 10;

  Cube c(10., glm::dvec3(2., size-1, 4.));
  CubeRenderer cr(c);
  c.setPosition(glm::dvec3(0., size * n, 0.));
  e.add(c, cr);

  Plan p(glm::dvec3(0., 0., 0.), glm::dvec3(0., 1., 0.));
  PlanRenderer pr(p);
  e.add(p, pr);

  DistancePointConstraint dc2(c, glm::dvec3(0., size * n + 10 , 0.), glm::dvec3(0., 0.5, 0.));
  physics.add(dc2);


  Cube *prec = &c;
  for(int i = 1 ; i < n ; i++){
    Cube *c = new Cube(10., glm::dvec3(2., size-1, 4.));
    CubeRenderer *cr = new CubeRenderer(*c);
    e.add(*c, *cr);

    c->setPosition(glm::dvec3(0., size * (n - i), 0.));

    DistanceConstraint *dc = new DistanceConstraint(
        *c, *prec, glm::dvec3(0., 0.5, 0.), glm::dvec3(0., -0.5, 0.));

    physics.add(*dc);

    prec = c;
  }

  prec->setLinearVelocity(glm::dvec3(50., 0., 0.));

  call_gl(argc, argv, e);

  return 0;
}
