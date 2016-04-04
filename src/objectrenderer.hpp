#pragma once

#include <GL/gl.h>

#include "glm/gtc/type_ptr.hpp"
#include "object.hpp"

class ObjectRenderer{
  public:
    virtual void render(double alpha = 1.) = 0;
};
