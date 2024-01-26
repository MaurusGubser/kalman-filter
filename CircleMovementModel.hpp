#pragma once

#include <array>
#include <iostream>

class CircleMovement
{
private:
    float theta;
    float x;
    float y;

public:
    CircleMovement();
    CircleMovement(float);
    CircleMovement(float, float);
    float get_angle();
    std::array<float, 2> get_position();
    float observe_distance(float);
    void make_n_steps(int);
    void print_position();
    void print_observation(float);
};
