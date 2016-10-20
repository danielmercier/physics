#include "constraint.hpp"

const double Constraint::bias_factor = 0.5;

Constraint::Constraint(){
  setBias(arma::mat{1.0});
  must_apply = false;
}

arma::mat Constraint::solve(){
  if(update()){
    must_apply = true;
    arma::mat lambda = arma::solve(jacobian * invmass * jacobian.t(),
                                  - (jacobian * velocity + bias));

    return lambda;
  }

  must_apply = false;
  return { 0. };
}

arma::mat Constraint::getVelocities(arma::mat lambda){
  arma::mat vel = velocity;
  if(must_apply){
    arma::mat Pc;
    if(lambda.n_rows == 1 && lambda.n_cols == 1){
      Pc = jacobian.t() * lambda[0];
    } else {
      Pc = jacobian.t() * lambda;
    }

    vel = velocity + invmass * Pc;
  }

  return vel;
}

bool Constraint::mustBeApplied(){
  return must_apply;
}

void Constraint::setBias(arma::mat bias){
  this->bias = bias_factor * bias;
}

void Constraint::setBias(double bias){
  this->bias = bias_factor * bias;
}
