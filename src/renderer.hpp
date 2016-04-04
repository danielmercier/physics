#pragma once

#include <GL/gl.h>
#include <GL/glut.h>
#include <list>

#include "objectrenderer.hpp"

class Renderer{
  private:
    std::list<ObjectRenderer*> objects;

  public:
    /* Definitions des matériaux */
    static const GLfloat mat_specularWHITE[];
    static const GLfloat mat_ambientWHITE[];
    static const GLfloat mat_diffuseWHITE[];
    static const GLfloat mat_shininessWHITE[];

    static const GLfloat mat_specularGRAY[];
    static const GLfloat mat_ambientGRAY[];
    static const GLfloat mat_diffuseGRAY[];
    static const GLfloat mat_shininessGRAY[];

    static const GLfloat mat_specularBLUE[];
    static const GLfloat mat_ambientBLUE[];
    static const GLfloat mat_diffuseBLUE[];
    static const GLfloat mat_shininessBLUE[];

    static const GLfloat mat_specularGREEN[];
    static const GLfloat mat_ambientGREEN[];
    static const GLfloat mat_diffuseGREEN[];
    static const GLfloat mat_shininessGREEN[];

    static const GLfloat mat_specularYELLOW[];
    static const GLfloat mat_ambientYELLOW[];
    static const GLfloat mat_diffuseYELLOW[];
    static const GLfloat mat_shininessYELLOW[];

    static const GLfloat mat_specularRED[];
    static const GLfloat mat_ambientRED[];
    static const GLfloat mat_diffuseRED[];
    static const GLfloat mat_shininessRED[];

    /* Encapsulation des fonctions matériaux */
    static void set_material(const GLfloat spec[], const GLfloat amb[], const GLfloat diff[], const GLfloat shin[]);

    void add(ObjectRenderer *o);

    void render(double alpha);
};
