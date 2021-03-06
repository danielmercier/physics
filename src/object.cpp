#include "object.hpp"

/*Constructeur de base*/
Object::Object(){
  current.position = { 0., 0., 0. };
  current.orientation = { 0., 0., 0., 0. };
#ifdef RK4
  current.momentum = { 0., 0., 0. };
  current.angularMomentum = { 0., 0., 0. };
#endif
  current.mass = -1.;
  current.inverseMass = 0.;
  current.inertiaTensor = glm::mat3(-1.);
  current.inverseInertiaTensor = glm::mat3(0.);
  current.recalculate();

  previous = current;
}

Object::~Object(){
  delete _collisionShape;
}

Object::State Object::previousState(){
  return previous;
}

Object::State Object::interpolate(double alpha){
  return interpolate(previous, current, alpha);
}

std::list<glm::dvec3> Object::getVertices(){
  return vertices;
}

bool Object::collide(Object &other, std::list<Contact> &contact){
  return _collisionShape->intersectVisit(other._collisionShape, contact);
}

#ifdef RK4
// Mise a jour de l'état physique de l'objet
void Object::update(double t, double dt){
  previous = current;
  integrate(current, t, dt);
}

Object::State Object::interpolate(const Object::State &a, const Object::State &b, double alpha){
  State state = b;
  state.position = glm::mix(a.position, b.position, alpha);
  state.momentum = glm::mix(a.momentum, b.momentum, alpha);
  state.orientation = glm::mix(a.orientation, b.orientation, alpha);
  state.angularMomentum = glm::mix(a.angularMomentum, b.angularMomentum, alpha);
  state.recalculate();
  return state;
}
#else
Object::State Object::interpolate(const Object::State &a, const Object::State &b, double alpha){
  State state = b;
  state.position = glm::mix(a.position, b.position, alpha);
  state.velocity = glm::mix(a.velocity, b.velocity, alpha);
  state.orientation = glm::mix(a.orientation, b.orientation, alpha);
  state.angularVelocity = glm::mix(a.angularVelocity, b.angularVelocity, alpha);
  state.recalculate();
  return state;
}
#endif

#ifdef RK4
Object::Derivative Object::evaluate(Object::State state, double t){
  Derivative output;
  output.velocity = state.velocity;
  output.spin = state.spin;
  forces(state, t, output.force, output.torque);
  return output;
}

Object::Derivative Object::evaluate(State state, double t, double dt, const Derivative &derivative){
  state.position += derivative.velocity * dt;
  state.momentum += derivative.force * dt;
  state.orientation += derivative.spin * dt;
  state.angularMomentum += derivative.torque * dt;
  state.recalculate();

  Derivative output;
  output.velocity = state.velocity;
  output.spin = state.spin;
  forces(state, t+dt, output.force, output.torque);
  return output;
}

void Object::integrate(Object::State &state, double t, double dt)
{
  Derivative a = evaluate(state, t);
  Derivative b = evaluate(state, t, dt * .5, a);
  Derivative c = evaluate(state, t, dt * .5, b);
  Derivative d = evaluate(state, t, dt, c);

  state.position += 1./6. * dt * (a.velocity + 2.*(b.velocity + c.velocity) + d.velocity);
  state.momentum += 1./6. * dt * (a.force + 2.*(b.force + c.force) + d.force);
  state.orientation += 1./6. * dt * (a.spin + 2.*(b.spin + c.spin) + d.spin);
  state.angularMomentum += 1./6. * dt * (a.torque + 2.*(b.torque + c.torque) + d.torque);

  state.recalculate();
}
#endif

void Object::forces(const State &state, double t, glm::dvec3 &force, glm::dvec3 &torque){
  force = glm::dvec3(0., -9.8 * state.mass, 0.);
}

void Object::integrateForces(double dt){
  glm::dvec3 force;
  glm::dvec3 torque;

  forces(current, 0., force, torque);

  current.velocity += force * dt * current.inverseMass;
  current.angularVelocity += torque * dt * current.inverseInertiaTensor;
}

void Object::integrateVelocities(double dt){
  current.position += current.velocity * dt;

  glm::dquat spin = 0.5 * glm::dquat(0.0, current.angularVelocity.x, current.angularVelocity.y, current.angularVelocity.z) * current.orientation;

  current.orientation += spin * dt;
}

void Object::setPosition(glm::dvec3 pos){
  current.position = pos;
  current.recalculate();
}

void Object::setScaling(glm::dvec3 scaling){
  current.scaling = scaling;
  current.recalculate();
}

void Object::setOrientation(glm::quat orientation){
  current.orientation = orientation;
  current.recalculate();
}

void Object::setLinearVelocity(glm::dvec3 vel){
  current.velocity = vel;
}

void Object::setAngularVelocity(glm::dvec3 vel){
  current.angularVelocity = vel;
}

glm::dvec3 Object::toWorld(const glm::dvec3 &point, double homogeneous){
  return glm::dvec3(current.bodyToWorld * glm::dvec4(point, homogeneous));
}

glm::dvec3 Object::getPosition(){
  return current.position;
}

glm::dvec3 Object::getLinearVelocity(){
  return current.velocity;
}

glm::dvec3 Object::getAngularVelocity(){
  return current.angularVelocity;
}

Object::State Object::getState(){
  return current;
}

void Object::recalculate(){
  current.recalculate();
}
