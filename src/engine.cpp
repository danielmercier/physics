#include "engine.hpp"

double Engine::gettime(){
  return glutGet(GLUT_ELAPSED_TIME) / 1000;
}

Engine::Engine(){
  currentTime = gettime();
  accumulator = 0.0;
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
