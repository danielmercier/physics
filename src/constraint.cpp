#include "constraint.hpp"

Constraint::Constraint(){
  bias = 0.05;
}

arma::mat Constraint::solve(){
  if(update()){
    arma::mat lambda = arma::solve(jacobian * invmass * jacobian.t(),
                                  - (jacobian * velocity + bias));
    return lambda;
  }

  return { 0. };
}

arma::mat Constraint::getVelocities(arma::mat lambda){
    arma::mat Pc =  lambda * jacobian.t();
    arma::mat vel = velocity + invmass * Pc;
    return vel;
}

arma::mat Constraint::getVelocities(double lambda){
    arma::mat Pc =  lambda * jacobian.t();
    arma::mat vel = velocity + invmass * Pc;
    return vel;
}
