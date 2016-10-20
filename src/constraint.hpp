#pragma once

#include <armadillo>
#include "glm/glm.hpp"
#include "global_const.hpp"

class Constraint{
  private:
    static const double bias_factor;
    arma::mat bias;
    bool must_apply;

  protected:
    arma::mat jacobian;
    arma::mat invmass;
    arma::mat velocity;

    //Met a jour et indique si la contrainte doit être appliquée
    virtual bool update() = 0;



    //retourne le vecteur des nouvelles vitesses
    arma::mat getVelocities(arma::mat lambda);

  public:
    Constraint();

    arma::mat solve();

    //applique lambda
    virtual void apply(arma::mat lambda) = 0;
    bool mustBeApplied();

    void setBias(arma::mat bias);
    void setBias(double bias);
};
