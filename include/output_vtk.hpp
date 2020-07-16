#ifndef __OUTPUT
#define __OUTPUT
#include"hedder.hpp"
class output
{
    private:

    public:
        void output_pressure_vtk(int NN, int NE, std::vector<double> X, std::vector<double> Y, std::vector<int> NP1, std::vector<int> NP2, std::vector<int> NP3, std::vector<double> p);
        void calculate_velocity(int NE, std::vector<double> &vx,std::vector<double> &vy,std::vector<double> B1,std::vector<double> B2,std::vector<double> B3,std::vector<double> C1, std::vector<double> C2, std::vector<double> C3, std::vector<double> p, std::vector<int> N1, std::vector<int> N2, std::vector<int> N3);
        void output_velocity_vtk(int NE, std::vector<double> vx, std::vector<double> vy, std::vector<double> G_X, std::vector<double> G_Y);
};

#endif