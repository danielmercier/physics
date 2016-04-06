#include "physicsengine.hpp"

#include "distanceconstraint.hpp"
#include "converter.hpp"

PhysicsEngine::PhysicsEngine(Solver &sol){
  ownsolver = false;
  solver = &sol;
}

PhysicsEngine::PhysicsEngine(){
  ownsolver = true;
  solver = new SequentialSolver(100);
}

PhysicsEngine::~PhysicsEngine(){
  if(ownsolver){
    delete solver;
  }
}

bool equal(double a, double b){
  const double tol = 1e-10;
  return (abs(a - b) <= tol);
}

bool equal(glm::dvec3 a, glm::dvec3 b){
  glm::dvec3 res = abs(a - b);
  return equal(res.x, 0.) &&
         equal(res.y, 0.) &&
         equal(res.z, 0.);
}

void PhysicsEngine::add(Constraint &c){
  solver->add(c);
}

void PhysicsEngine::add(Object *o){
  objects.push_back(o);
}

void PhysicsEngine::update(double t, double dt){
  static int nbCol = 0;
  std::list<Contact> contact;

  for(auto o : objects){
    o->integrateForces(dt);
  }

  solver->solve();

  for(auto o : objects){
    o->integrateVelocities(dt);
    o->recalculate();
  }
}

//double PhysicsEngine::get_impulse(const Object::State &obj1, const Object::State &obj2, const Contact &c){
//  glm::dvec3 ra = obj1.position - c.impact;
//  glm::dvec3 rb = obj2.position - c.impact;
//
//  glm::dvec3 racross = glm::cross(ra, c.normal);
//  glm::dvec3 rbcross = glm::cross(rb, c.normal);
//
//  double num = glm::dot(obj2.velocity - obj1.velocity, c.normal);
//  num += glm::dot(racross, obj1.angularVelocity);
//  num += glm::dot(rbcross, obj2.angularVelocity);
//
//  double den = obj1.inverseMass + obj2.inverseMass;
//  den += glm::dot(racross, obj1.inverseInertiaTensor * racross);
//  den += glm::dot(rbcross, obj2.inverseInertiaTensor * rbcross);
//
//  return (- (1. + c.restitution) * num / den);
//}
//
//void PhysicsEngine::apply_impulse(Object::State &obj1, Object::State &obj2, const Contact &c, double j){
//  glm::dvec3 ra = obj1.position - c.impact;
//  glm::dvec3 rb = obj2.position - c.impact;
//
//  /*Reaction de l'objet 1*/
//  double jr = std::min(j, 0.);
//  glm::dvec3 J =  jr * c.normal;
//
//  obj1.momentum -= J;
//  obj1.angularMomentum -= glm::cross(J, ra);
//  /***********************/
//
//
//  /*Reaction de l'objet 2*/
//  jr = std::max(j, 0.);
//  J =  jr * c.normal;
//
//  obj2.momentum += J;
//  obj2.angularMomentum -= glm::cross(J, rb);
//  /***********************/
//}
//
//double PhysicsEngine::apply_friction(Object::State &obj, double tim, const Contact &c, double jr){
//  glm::dvec3 t = glm::dvec3(0.);
//  glm::dvec3 vr = obj.point_velocity(c.impact);
//  glm::dvec3 force;
//  glm::dvec3 torque;
//  Object::forces(obj, tim, force, torque);
//
//  if(!equal(glm::dot(vr, c.normal), 0.)){
//    t = vr - glm::dot(vr, c.normal) * c.normal;
//
//    if(equal(t, glm::dvec3(0.)))
//      t = glm::dvec3(0.);
//    else
//      t = glm::normalize(t);
//  }
//  else if(!equal(glm::dot(force, c.normal), 0.)){
//    t = glm::normalize(force - glm::dot(force, c.normal) * c.normal);
//
//    if(equal(t, glm::dvec3(0.)))
//      t = glm::dvec3(0.);
//    else
//      t = glm::normalize(t);
//  }
//
//  double js = c.static_friction * jr;
//  double jd = c.dynamic_friction * jr;
//
//  glm::dvec3 jf;
//
//  jf = -jd * t;
//
//  /*Reaction de l'objet*/
//  obj.momentum += jf;
//  obj.angularMomentum -= glm::cross(jf, obj.position - c.impact);
//  /*********************/
//
//  return jr - jd;
//}
