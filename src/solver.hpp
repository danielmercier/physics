#pragma once

#include <list>

#include "constraint.hpp"

class Solver{
  protected:
    std::list<Constraint*> constraints;

  public:
    void add(Constraint &constraint){
      constraints.push_back(&constraint);
    }

    virtual void solve() = 0;
};
