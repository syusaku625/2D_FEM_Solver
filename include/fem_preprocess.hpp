#ifndef __PROCESS
#define __PROCESS
#include"hedder.hpp"

class PreProcess{
    private:

    public:
        void make_stiffness_matrix(std::vector<std::vector<double>> &G, int NE, std::vector<int> NP1, std::vector<int> NP2, std::vector<int> NP3, std::vector<double> X, std::vector<double> Y);
        void set_dirichlet_boundary_condition(std::vector<std::vector<double>> &G, std::vector<double> &R, int NN, int NN2, int NN3, std::vector<int> IFIX_in, std::vector<int> IFIX_out, double in_pressure, double out_pressure);
};

#endif