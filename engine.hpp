#pragma once

#include <time.h>
#include <GL/glut.h>

#include "object.hpp"
#include "objectrenderer.hpp"
#include "physicsengine.hpp"
#include "renderer.hpp"

class Engine{
  private:
    double t;
    const double dt = 0.01;
    double currentTime;
    double accumulator;

    PhysicsEngine physics;
    Renderer renderer;

    static double gettime(){
      return glutGet(GLUT_ELAPSED_TIME) / 1000;
    }

  public:
    Object obj;
    ObjectRenderer objrenderer;

    Object obj2;
    ObjectRenderer objrenderer2;

    Engine() : objrenderer(obj), objrenderer2(obj2){
      currentTime = gettime();
      accumulator = 0.0;

      obj.test1();
      obj2.test1();
      add(obj, objrenderer);
      renderer.add(&objrenderer2);
    }

    void add(Object &op, ObjectRenderer &ore){
      physics.add(&op);
      renderer.add(&ore);
    }

    void update(){
        double newTime = gettime();
        double frameTime = newTime - currentTime;

        if( frameTime > 0.25 )
          frameTime = 0.25;

        currentTime = newTime;

        accumulator += frameTime;

        //while( accumulator >= dt ){
        //  physics.update( t, dt );

        //  t += dt;
        //  accumulator -= dt;
        //}
        physics.update( t, dt );
        t += dt;

        double alpha = accumulator / dt;
        renderer.render( alpha );
      }
};
