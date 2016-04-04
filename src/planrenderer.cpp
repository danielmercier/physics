#include "planrenderer.hpp"

PlanRenderer::PlanRenderer(Plan &o){
  this->plan = &o;
}

void PlanRenderer::Draw3DSGrid() {
  glm::dvec3 axe = glm::cross(plan->normal, glm::dvec3(0., 1., 0.));
  axe = glm::normalize(axe);
  double rotation = glm::dot(plan->normal, glm::dvec3(0., 1., 0.));
  rotation = acos(rotation);
  rotation = -rotation * 180 / M_PI;

  glTranslated(plan->origin.x, plan->origin.y, plan->origin.z);
  glRotatef(rotation, axe.x, axe.y, axe.z);

  Renderer::set_material(Renderer::mat_specularGRAY,
                        Renderer::mat_ambientGRAY,
                        Renderer::mat_diffuseGRAY,
                        Renderer::mat_shininessGRAY);

  glColor3f(0.0, 0.0, 0.0);
  float i;
  for(i = -50; i <= 50; i += 5) {
    glBegin(GL_LINES);
    glVertex3f(-50, 0, i);
    glVertex3f(50, 0, i);
    glVertex3f(i, 0, -50);
    glVertex3f(i, 0, 50);
    glEnd();
  }
}

void PlanRenderer::render(double alpha){
  Draw3DSGrid();
}
