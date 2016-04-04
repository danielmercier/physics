#include "engine.hpp"

double Engine::gettime(){
  return glutGet(GLUT_ELAPSED_TIME) / 1000;
}

Engine::Engine() : objrenderer(obj),
           objrenderer2(obj2),
           objrenderer3(obj3),
           objrenderer4(obj4),
           objrenderer5(obj5),
           obj(10., glm::dvec3(5.0, 2.0, 5.0)),
           obj2(glm::dvec3(0., 0., 0.), glm::dvec3(0., 1., 0.)),
           obj3(glm::dvec3(0., 0., 0.), glm::dvec3(-0.5, 1., 0.)),
           obj4(glm::dvec3(0., 30., 0.), glm::dvec3(0.5, -1., 0.)),
           obj5(glm::dvec3(0., 30., 0.), glm::dvec3(-0.5, -1., 0.)){
  currentTime = gettime();
  accumulator = 0.0;

  Object::State *s = obj.state();
  s->position = glm::dvec3(0., 20., 0.);
  //s->orientation = glm::quat(M_PI / 6, 0, 1, 1);
  s->recalculate();

  add(obj, objrenderer);
  add(obj2, objrenderer2);
  //add(obj3, objrenderer3);
  //add(obj4, objrenderer4);
  //add(obj5, objrenderer5);
}

void Engine::add(Object &op, ObjectRenderer &ore){
  physics.add(&op);
  renderer.add(&ore);
}

void Engine::update(){
  double newTime = gettime();
  double frameTime = newTime - currentTime;

  if( frameTime > 0.25 )
    frameTime = 0.25;

  currentTime = newTime;

  accumulator += frameTime;

  //while( accumulator >= dt ){
  //  physics.update( t, dt );

  //  t += dt;
  //  accumulator -= dt;
  //}
  //
  if(!this->pause){
    physics.update( t, dt );
  }
  t += dt;

  double alpha = accumulator / dt;
  alpha = 1.;
  renderer.render( alpha );
}

void Engine::run_pause(){
  this->pause = !this->pause;
}
