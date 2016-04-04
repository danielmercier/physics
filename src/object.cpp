#include "object.hpp"

/*Constructeur de base*/
Object::Object(){
  current.position = { 0., 0., 0. };
  current.momentum = { 0., 0., 0. };
  current.orientation = { 0., 0., 0., 0. };
  current.angularMomentum = { 0., 0., 0. };
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

Object::State * Object::state(){
  return &current;
}

Object::State Object::previousState(){
  return previous;
}

// Mise a jour de l'état physique de l'objet
void Object::update(double t, double dt){
  previous = current;
  integrate(current, t, dt);
}

Object::State Object::interpolate(double alpha){
  return interpolate(previous, current, alpha);
}

std::list<glm::dvec3> Object::get_vertices(){
  return vertices;
}

bool Object::collide(Object &other, std::list<Contact> &contact){
  return _collisionShape->intersectVisit(other._collisionShape, contact);
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

void Object::forces(const State &state, double t, glm::dvec3 &force, glm::dvec3 &torque){
  force = glm::dvec3(0., -5. * state.mass, 0.);
}
