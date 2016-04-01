#pragma once

#include <GL/gl.h>

#include "glm/gtc/type_ptr.hpp"
#include "object.hpp"

class ObjectRenderer{
  private:
    Object *obj;

  public:
    ObjectRenderer(Object &o){
      this->obj = &o;
    }

    void render(float alpha = 1.f){
      glPushMatrix();

      Object::State s = obj->interpolate(alpha);

      //glMultMatrixf(glm::value_ptr(s.bodyToWorld));
      glMultMatrixf(glm::value_ptr(obj->getBodyToWorld()));

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
};
