#pragma once

#include <list>

class Renderer{
  private:
    std::list<ObjectRenderer*> objects;

  public:
    void add(ObjectRenderer *o){
      objects.push_back(o);
    }

    void render(double alpha){
      for(auto o : objects){
        o->render( alpha );
      }
    }
};
