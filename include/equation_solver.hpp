#ifndef __SOLVER
#define __SOLVER
#include"hedder.hpp"
class Solver{
    private:
        std::vector<double> tmp_p;

    public:
        void Jacobi_method(std::vector<double> &p, std::vector<double> &R, std::vector<std::vector<double>> &G, int NN, double convergence);
};
#endif