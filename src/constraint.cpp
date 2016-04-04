#include "constraint.hpp"

Constraint::Constraint(arma::mat jacobian, arma::vec invmass, arma::vec velocity, double bias){
  this->jacobian = jacobian;
  this->invmass = invmass;
  this->velocity = velocity;
}

Constraint::Constraint(){
  bias = 0.;
}

double Constraint::solve(){
  arma::vec lambda = (- (jacobian * velocity + bias) / (jacobian * invmass * jacobian.t()));
  return lambda[0];
}

arma::vec Constraint::apply(double lambda){
  arma::vec Pc = jacobian.t() * lambda;
  arma::vec vel = velocity * invmass * Pc;
  return vel;
}
