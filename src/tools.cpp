#include <iostream>
#include "tools.h"

using namespace std;
using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  VectorXd rmse(4);
  rmse << 0, 0, 0, 0;

  if(estimations.size() != ground_truth.size()
     || estimations.size() == 0) {
    cout << "Estimations is either empty or differs from ground truth" << endl;
    return rmse;
  }

  //accumulate squared residuals
  VectorXd residuals(4);
  residuals << 0.0, 0.0, 0.0, 0.0;
  for(int i=0; i < estimations.size(); ++i){
    VectorXd residual = estimations[i] - ground_truth[i];
    residual = residual.array() * residual.array();
    residuals += residual;
  }

  //calculate the mean
  residuals = residuals/estimations.size();

  //calculate the squared root
  rmse = residuals.array().sqrt();

  return rmse;
}
