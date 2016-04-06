#include "cuberenderer.hpp"

CubeRenderer::CubeRenderer(Cube &o){
  this->cube = &o;
}

void CubeRenderer::render(double alpha){
  glPushMatrix();

  Object::State s = cube->interpolate(alpha);

  glMultMatrixd(glm::value_ptr(s.bodyToWorld));

  glutSolidCube(1.0);

  glPopMatrix();
}
