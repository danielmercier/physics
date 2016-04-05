#pragma once

#include <algorithm>
#include <list>

#define GLM_PRECISION_HIGHP_DOUBLE
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shape.hpp"
#include "contact.hpp"

/* Un objet au sens physique */
class Object{

  public:
    struct State{
      // Etat primaire
      glm::dvec3 position;
      glm::dquat orientation;

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
#ifdef RK4
      glm::dvec3 momentum;
      glm::dvec3 angularMomentum;

      void recalculate(){
        velocity = momentum * inverseMass;
        angularVelocity = angularMomentum * inverseInertiaTensor;
        orientation = glm::normalize(orientation);
        spin = 0.5 * glm::dquat(0.0, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
        bodyToWorld = glm::translate(glm::dmat4(1.0), position) * glm::mat4_cast(orientation);
        worldToBody = glm::inverse(bodyToWorld);
      }
#else
      void recalculate(){
        orientation = glm::normalize(orientation);
        bodyToWorld = glm::translate(glm::dmat4(1.0), position) * glm::mat4_cast(orientation);
        worldToBody = glm::inverse(bodyToWorld);
      }
#endif

      glm::dvec3 abs_point_velocity(const glm::dvec3 &point){
        return velocity + glm::cross(angularVelocity, point);
      }

      glm::dvec3 point_velocity(const glm::dvec3 &point){
        return abs_point_velocity(point - position);
      }
    };

    /*Constructeur de base*/
    Object();
    ~Object();
    State * state();
    State previousState();
    // Mise a jour de l'état physique de l'objet
    void update(double t, double dt);
    void integrateForces(double dt);
    void integrateVelocities(double dt);
    State interpolate(double alpha);
    std::list<glm::dvec3> get_vertices();
    bool collide(Object &other, std::list<Contact> &contact);

    void setPosition(glm::dvec3 pos);
    void setLinearVelocity(glm::dvec3 vel);
    void setAngularVelocity(glm::dvec3 vel);

    static void forces(const State &state, double t, glm::dvec3 &force, glm::dvec3 &torque);

  protected:
    std::list<glm::dvec3> vertices;
    Shape *_collisionShape;
    State current;
    State previous;

  private:

    static State interpolate(const State &a, const State &b, double alpha);
    struct Derivative
    {
      glm::dvec3 velocity;
      glm::dvec3 force;
      glm::dquat spin;
      glm::dvec3 torque;
    };
    static Derivative evaluate(State state, double t);
    static Derivative evaluate(State state, double t, double dt, const Derivative &derivative);
    static void integrate(State &state, double t, double dt);
};
