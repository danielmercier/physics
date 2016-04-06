#pragma once

#include "solver.hpp"

#include <armadillo>

class SequentialSolver : public Solver{
  private:
    int max_iter;

  public:
    SequentialSolver(int max_iter = 10);
    void solve();
};
