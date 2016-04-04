#include "cuberenderer.hpp"

CubeRenderer::CubeRenderer(Cube &o){
  this->cube = &o;
}

void CubeRenderer::render(double alpha){
  glPushMatrix();

  Object::State s = cube->interpolate(alpha);

  glMultMatrixd(glm::value_ptr(s.bodyToWorld));
  glMultMatrixd(glm::value_ptr(glm::scale(glm::dmat4(1.0), cube->scaling)));

  glBegin(GL_QUADS);
  glVertex3f(-1, 1, 1);
  glVertex3f(1, 1, 1);
  glVertex3f(1, -1, 1);
  glVertex3f(-1, -1, 1);
  glEnd();

  glRotatef(90, 0, 1, 0);

  glBegin(GL_QUADS);
  glVertex3f(-1, 1, 1);
  glVertex3f(1, 1, 1);
  glVertex3f(1, -1, 1);
  glVertex3f(-1, -1, 1);
  glEnd();

  glRotatef(90, 0, 1, 0);


  glBegin(GL_QUADS);
  glVertex3f(-1, 1, 1);
  glVertex3f(1, 1, 1);
  glVertex3f(1, -1, 1);
  glVertex3f(-1, -1, 1);
  glEnd();

  glRotatef(90, 0, 1, 0);

  glBegin(GL_QUADS);
  glVertex3f(-1, 1, 1);
  glVertex3f(1, 1, 1);
  glVertex3f(1, -1, 1);
  glVertex3f(-1, -1, 1);
  glEnd();

  glRotatef(90, 0, 1, 0);

  glBegin(GL_QUADS);
  glVertex3f(-1, 1, 1);
  glVertex3f(-1, 1, -1);
  glVertex3f(1, 1, -1);
  glVertex3f(1, 1, 1);
  glEnd();

  glRotatef(90, 1, 0, 0);


  glBegin(GL_QUADS);
  glVertex3f(-1, 1, 1);
  glVertex3f(-1, 1, -1);
  glVertex3f(1, 1, -1);
  glVertex3f(1, 1, 1);
  glEnd();

  glPopMatrix();
}
