#include "renderer.hpp"

const GLfloat Renderer::mat_specularWHITE[] ={255.0,255.0,255.0,1.0};
const GLfloat Renderer::mat_ambientWHITE[] ={255.0,255.0,255.0,1.0};
const GLfloat Renderer::mat_diffuseWHITE[] ={255.0,255.0,255.0,1.0};
const GLfloat Renderer::mat_shininessWHITE[] ={128.0 * 0.4};

const GLfloat Renderer::mat_specularGRAY[] ={0.75,0.75,0.75,1.0};
const GLfloat Renderer::mat_ambientGRAY[] ={0.5,0.5,0.5,1.0};
const GLfloat Renderer::mat_diffuseGRAY[] ={0.50,0.50,0.50,1.0};
const GLfloat Renderer::mat_shininessGRAY[] ={128.0 * 0.6};

const GLfloat Renderer::mat_specularBLUE[] ={0.75,0.75,0.75,1.0};
const GLfloat Renderer::mat_ambientBLUE[] ={0,0,1,1.0};
const GLfloat Renderer::mat_diffuseBLUE[] ={0.50,0.50,0.50,1.0};
const GLfloat Renderer::mat_shininessBLUE[] ={128.0 };

const GLfloat Renderer::mat_specularGREEN[] ={0.633, 0.727811, 0.633,1.0};
const GLfloat Renderer::mat_ambientGREEN[] ={0.0215, 0.1745, 0.0215,1.0};
const GLfloat Renderer::mat_diffuseGREEN[] ={0.07568, 0.61424, 0.07568,1.0};
const GLfloat Renderer::mat_shininessGREEN[] ={128.0};

const GLfloat Renderer::mat_specularYELLOW[] ={0.75,0.75,0.75,1.0};
const GLfloat Renderer::mat_ambientYELLOW[] ={1,1,0,1.0};
const GLfloat Renderer::mat_diffuseYELLOW[] ={0.50,0.50,0.50,1.0};
const GLfloat Renderer::mat_shininessYELLOW[] ={128.0};

const GLfloat Renderer::mat_specularRED[] ={0.75,0.75,0.75,1.0};
const GLfloat Renderer::mat_ambientRED[] ={1.0,0.0,0.0,1.0};
const GLfloat Renderer::mat_diffuseRED[] ={0.8,0.50,0.50,1.0};
const GLfloat Renderer::mat_shininessRED[] ={128.0};

void Renderer::set_material(const GLfloat spec[], const GLfloat amb[], const GLfloat diff[], const GLfloat shin[]){
  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, shin);
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}

void Renderer::add(ObjectRenderer *o){
  objects.push_back(o);
}

void Renderer::render(double alpha){
  for(auto o : objects){
    glPushMatrix();
    o->render( alpha );
    glPopMatrix();
  }
}
