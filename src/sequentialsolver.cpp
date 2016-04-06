#include "sequentialsolver.hpp"

SequentialSolver::SequentialSolver(int max_iter){
  this->max_iter = max_iter;
}

void SequentialSolver::solve(){
  arma::mat lambda;
  for(int i = 0 ; i < max_iter ; i++){
    for(auto c : constraints){
      lambda = c->solve();
      c->apply(lambda);
    }
  }
}
