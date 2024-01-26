#pragma once

#include <vector>
#include <Eigen/Dense>

class KalmanFilter
{
private:
    Eigen::VectorXd x;
    Eigen::MatrixXd F;
    Eigen::MatrixXd Q;
    Eigen::MatrixXd H;
    Eigen::MatrixXd R;
    unsigned int dim_x;
    unsigned int dim_y;
    Eigen::MatrixXd P;
    Eigen::VectorXd state_to_observation();
    void set_dimensions();
    void init_P(float);

public:
    KalmanFilter(Eigen::VectorXd, Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd, float);
    void update(Eigen::VectorXd);
    std::vector<float> get_state_estimation();
    std::vector<float> get_observation_estimation();
};
