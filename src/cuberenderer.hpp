#pragma once

#include "objectrenderer.hpp"
#include "cube.hpp"

class CubeRenderer : public ObjectRenderer{
  private:
    Cube *cube;

  public:
    CubeRenderer(Cube &o);
    void render(double alpha = 1.);
};
