#pragma once

#include <time.h>
#include <GL/glut.h>

#include "object.hpp"
#include "objectrenderer.hpp"
#include "physicsengine.hpp"
#include "renderer.hpp"

#include "plan.hpp"
#include "planrenderer.hpp"
#include "cube.hpp"
#include "cuberenderer.hpp"

class Engine{
  private:
    double t;
    const double dt = 0.1;
    double currentTime;
    double accumulator;
    bool pause = false;

    PhysicsEngine physics;
    Renderer renderer;

    static double gettime();

  public:
    Engine();
    void add(Object &op, ObjectRenderer &ore);
    void update();
    void run_pause();
};
