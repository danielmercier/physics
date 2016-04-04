#pragma once

#include <armadillo>

class Constraint{
  protected:
    arma::mat jacobian;
    arma::mat invmass;
    arma::vec velocity;
    double bias;

  public:
    Constraint(arma::mat jacobian, arma::vec invmass, arma::vec velocity, double bias = 0.);
    Constraint();

    double solve();

    arma::vec apply(double lambda);
};
