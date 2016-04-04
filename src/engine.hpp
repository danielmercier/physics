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
    Cube obj;
    CubeRenderer objrenderer;

    Plan obj2;
    PlanRenderer objrenderer2;

    Plan obj3;
    PlanRenderer objrenderer3;

    Plan obj4;
    PlanRenderer objrenderer4;

    Plan obj5;
    PlanRenderer objrenderer5;

    Engine();
    void add(Object &op, ObjectRenderer &ore);
    void update();
    void run_pause();
};
