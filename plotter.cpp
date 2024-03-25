#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <array>

class CircleMovement
{
private:
    float theta;
    float x;
    float y;

public:
    CircleMovement();
    CircleMovement(float theta);
    CircleMovement(float x, float y);
    float get_angle();
    std::array<float, 2> get_position();
    float observe_distance(float dist_observer_to_origin);
    void make_n_steps(int n);
    void print_position();
    void print_observation(float d_obs_to_origin);
};

CircleMovement::CircleMovement() : theta{0.0}, x{0.0}, y{0.0}
{
}

CircleMovement::CircleMovement(float theta) : theta{theta}, x{std::cos(theta)}, y{std::sin(theta)}
{
}

CircleMovement::CircleMovement(float x, float y) : theta{std::atan2(y, x)}, x{x}, y{x}
{
}

float CircleMovement::get_angle()
{
    return this->theta;
}

std::array<float, 2> CircleMovement::get_position()
{
    return {x, y};
}

float CircleMovement::observe_distance(float dist_observer_to_origin)
{
    std::mt19937 gen(0);
    std::normal_distribution d{0.0, 0.5};
    float noise = d(gen);
    float dist2 = std::pow(dist_observer_to_origin - x, 2) + std::pow(y, 2);
    return std::sqrt(dist2);
}

void CircleMovement::make_n_steps(int n)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::normal_distribution d{0.0, 0.1};
    for (size_t i = 0; i < n; i++)
    {
        theta += d(gen);
    }
    x = std::cos(theta);
    y = std::sin(theta);
}

void CircleMovement::print_position()
{
    std::cout << "(x, y)=(" << x << ", " << y << ")" << std::endl;
    std::cout << "theta=" << theta << std::endl;
}

void CircleMovement::print_observation(float d_obs_to_origin)
{
    std::cout << "Observed distance=" << this->observe_distance(d_obs_to_origin) << std::endl;
}

int main()
{
    float x_observer = 5.0;
    CircleMovement cm = CircleMovement(0.0);

    // Open a file to save the positions
    std::ofstream outfile("positions.txt");
    if (!outfile.is_open())
    {
        std::cerr << "Error: Unable to open file for writing positions." << std::endl;
        return 1;
    }

    for (size_t i = 0; i < 10; i++)
    {
        // Write position to the file
        auto position = cm.get_position();
        outfile << position[0] << " " << position[1] << std::endl;

        std::cout << "---------------Step " << i << "---------------" << std::endl;
        cm.make_n_steps(1);
        cm.print_position();
        cm.print_observation(x_observer);
    }

    // Close the file
    outfile.close();

    // Plot the positions using Gnuplot
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (!gnuplotPipe)
    {
        std::cerr << "Error: Unable to open Gnuplot pipe." << std::endl;
        return 1;
    }

    fprintf(gnuplotPipe, "plot 'positions.txt' with linespoints\n");
    fflush(gnuplotPipe);
    std::cout << "Plot generated successfully." << std::endl;

    pclose(gnuplotPipe);

    return 0;
}
