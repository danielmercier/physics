#pragma once

#include <algorithm>

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

void norm(double &x){
  if(abs(x) <= 0.){
    x = 0.;
  }
}

void norm(glm::dvec3 &v){
  norm(v.x);
  norm(v.y);
  norm(v.z);
}

/* Un objet au sens physique */
class Object{

  public:
    struct State{
      // Etat primaire
      glm::dvec3 position;
      glm::dvec3 momentum;
      glm::dquat orientation;
      glm::dvec3 angularMomentum;

      // Etat secondaire
      glm::dvec3 velocity;
      glm::dquat spin;
      glm::dvec3 angularVelocity;
      glm::dmat4 bodyToWorld;
      glm::dmat4 worldToBody;

      // Constants
      double mass; // mass infini = -1
      double inverseMass; // mass infini, inverseMass = 0
      glm::dmat3 inertiaTensor; // objet inerte, inertiatensor = -1
      glm::dmat3 inverseInertiaTensor; //objet inerte inverse = 0

      // Recalcule les valeurs secondaire en fonction des valeurs primaire
      void recalculate(){
        static int n = 0;
        if(n >= 20){
          n = 0;
          norm(momentum);
        }
        n++;
        velocity = momentum * inverseMass;
        angularVelocity = angularMomentum * inverseInertiaTensor;
        orientation = glm::normalize(orientation);
        spin = 0.5 * glm::dquat(0.0, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
        bodyToWorld = glm::translate(glm::dmat4(1.0), position) * glm::mat4_cast(orientation);
        worldToBody = glm::inverse(bodyToWorld);
      }
    };

    /*Constructeur de base*/
    Object(){
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

    State * state(){
      return &current;
    }

    State previousState(){
      return previous;
    }

    // Mise a jour de l'état physique de l'objet
    void update(double t, double dt){

      previous = current;
      integrate(current, t, dt);

    }

    State interpolate(double alpha){
      return interpolate(previous, current, alpha);
    }


    /******************TEST******************/
    /****************************************/

    void test1(){
      current.position = glm::dvec3(1., 10., 3.);
      current.momentum = glm::dvec3(0., 0., 3.);
      current.angularMomentum = glm::dvec3(0., 0., 0.);
      current.mass = 1.;
      current.inverseMass = 1.;
      current.inertiaTensor = glm::dmat3(2.);
      current.inverseInertiaTensor = glm::dmat3(0.5);

      current.recalculate();
    }

    void loop(){
      current.position += current.velocity;
      current.orientation += current.spin;
      current.recalculate();
    }

    glm::mat4 getBodyToWorld(){
      return current.bodyToWorld;
    }
    /****************************************/
    /****************************************/

  private:
    State current;
    State previous;

    static State interpolate(const State &a, const State &b, double alpha){
      State state = b;
      state.position = glm::mix(a.position, b.position, alpha);
      state.momentum = glm::mix(a.momentum, b.momentum, alpha);
      state.orientation = glm::mix(a.orientation, b.orientation, alpha);
      state.angularMomentum = glm::mix(a.angularMomentum, b.angularMomentum, alpha);
      state.recalculate();
      return state;
    }

    struct Derivative
    {
      glm::dvec3 velocity;
      glm::dvec3 force;
      glm::dquat spin;
      glm::dvec3 torque;
    };

    static Derivative evaluate(State state, double t){
      Derivative output;
      output.velocity = state.velocity;
      output.spin = state.spin;
      forces(state, t, output.force, output.torque);
      return output;
    }

    static Derivative evaluate(State state, double t, double dt, const Derivative &derivative){
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

    static void integrate(State &state, double t, double dt)
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

    static void forces(const State &state, double t, glm::dvec3 &force, glm::dvec3 &torque){
      force = glm::dvec3(0., -10., 0.);
    }
};
