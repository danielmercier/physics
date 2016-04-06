#pragma once

#include <armadillo>

class Constraint{
  private:
    arma::mat bias;

  protected:
    arma::mat jacobian;
    arma::mat invmass;
    arma::mat velocity;

    //Met a jour et indique si la contrainte doit être appliquée
    virtual bool update() = 0;


    //retourne le vecteur des nouvelles vitesses
    arma::mat getVelocities(arma::mat lambda);
    arma::mat getVelocities(double);

  public:
    Constraint();

    arma::mat solve();

    //applique lambda
    virtual void apply(arma::mat lambda) = 0;
};
