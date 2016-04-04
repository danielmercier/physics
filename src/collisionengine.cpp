#include "collisionengine.hpp"
#include "cubeshape.hpp"
#include "planshape.hpp"

bool CollisionEngine::test_collide(PlanShape *cube, CubeShape *plan, std::list<Contact> &contact){
  return test_collide(plan, cube, contact);
}

bool CollisionEngine::test_collide(CubeShape *cube1, CubeShape *cube2, std::list<Contact> &contact){
  return false;
}

bool CollisionEngine::test_collide(PlanShape *plan1, PlanShape *plan2, std::list<Contact> &contact){
  return false;
}

bool CollisionEngine::test_collide(CubeShape *cube, PlanShape *plan, std::list<Contact> &contact){
  Cube *c = cube->cube;
  Contact cont;
  bool collision = false;
  glm::dvec3 normal = plan->plan->normal;
  glm::dvec3 origin = plan->plan->origin;

  for(glm::dvec3 &vertex : c->get_vertices()){
    glm::dvec3 v = glm::dvec3(c->state()->bodyToWorld * glm::dvec4(vertex, 1));
    v = v - origin;
    double dot = glm::dot(normal, v);
    if(dot <= 0){
      cont.impact = v + origin;
      cont.normal = normal;
      cont.restitution = 0.99;
      cont.static_friction = 0.1;
      cont.dynamic_friction = 0.1;
      contact.push_back(cont);

      collision = true;
    }
  }

  return collision;
}
