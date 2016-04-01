#pragma once

#include <list>
#include <algorithm>

#include "object.hpp"

bool equal(double a, double b){
  return(abs(a - b) <= 0. * std::max(abs(a), abs(b)) * std::numeric_limits<double>::epsilon());
}

class PhysicsEngine{
  private:
    std::list<Object*> objects;

  public:
    void add(Object *o){
      objects.push_back(o);
    }

    void update(double t, double dt){
      for(auto o : objects){

        Object::State *state = o->state();
        double prof;
        double alpha = 1.;
        if(test_collide(*state, prof)){
          //*state = search_collide_point(*o, alpha);
          state->position.y = 0;

          double d = glm::dot(state->momentum, glm::dvec3(0., 1., 0.));
          //float j = std::max( - ( .9f + 1.f ) * d, 0.f );
          double j = - ( 0.5 + 1. ) * state->momentum.y;
          state->momentum += j * glm::dvec3( 0., 1., 0. );

          state->recalculate();
        }
        printf("%lf\n", state->position.y);

        o->update(t, dt + (1. - alpha) * dt);
      }
    }

    // Cherche entre [0..alpha] pour trouver la position de l'impact exact
    static Object::State search_collide_point(Object &o, double &alpha){
      Object::State lastcollide = *o.state();

      alpha = 1.;
      double borne_inf = 0.;
      double borne_sup = alpha;
      bool not_found = true;

      while(not_found){
        alpha = (borne_sup + borne_inf) / 2.;
        Object::State now = o.interpolate( alpha );

        double prof;
        bool collide = test_collide( now, prof );

        if ( collide ){
          if (equal(prof, 0.)){
            printf("%lf", prof);
            not_found = false;
          }
          else{
            borne_sup = alpha;
          }

          lastcollide = now;
        }
        else{
          borne_inf = alpha;
        }
      }

      return lastcollide;
    }

    static bool test_collide(Object::State &s, double &prof){
        if(s.position.y <= 0){
          prof = s.position.y;
          return true;
        }
        else{
          return false;
        }
    }

    static const int pas_dicho = 100;
};
