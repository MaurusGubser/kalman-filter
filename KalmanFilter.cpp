#include <vector>
#include "KalmanFilter.hpp"

KalmanFilter::KalmanFilter(Eigen::VectorXd x0, Eigen::MatrixXd F, Eigen::MatrixXd Q, Eigen::MatrixXd H, Eigen::MatrixXd R, float sigma_init)
    : x{x0}, F{F}, Q{Q}, H{H}, R{R}
{
    set_dimensions();
    init_P(sigma_init);
}

Eigen::VectorXd KalmanFilter::state_to_observation()
{
    return H * x;
}

void KalmanFilter::set_dimensions()
{
    dim_x = H.rows();
    dim_y = H.cols();
}

void KalmanFilter::init_P(float sigma)
{
    P = sigma * Eigen::MatrixXd::Identity(dim_x, dim_x);
}

void KalmanFilter::update(Eigen::VectorXd y_t)
{
    Eigen::VectorXd innovation = y_t - H * F * x;
    P = F*P*F.transpose() + Q;
    Eigen::MatrixXd innovation_covar = H*P*H.transpose() + R;
    Eigen::MatrixXd K_gain = P*H.transpose() * innovation_covar.inverse();
    x = F*x + K_gain * innovation;
    P = (Eigen::MatrixXd::Identity(dim_x, dim_x) - K_gain * H) *P;
}