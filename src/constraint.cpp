#include "constraint.hpp"


Constraint::Constraint(){
  bias_factor = 0.1;
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
  this->bias = bias_factor / DELTA_T * bias;
}

void Constraint::setBias(double bias){
  this->bias = bias_factor / DELTA_T * bias;
}

void Constraint::setBiasFactor(double bias_factor){
  this->bias_factor = bias_factor;
}
