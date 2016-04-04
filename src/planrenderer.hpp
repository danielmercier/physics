#pragma once

#include <GL/gl.h>

#include "glm/gtc/type_ptr.hpp"
#include "renderer.hpp"
#include "objectrenderer.hpp"
#include "plan.hpp"

class PlanRenderer : public ObjectRenderer{
  protected:
    Plan *plan;

  public:
    PlanRenderer(Plan &o);

    void Draw3DSGrid();

    void render(double alpha = 1.);
};
