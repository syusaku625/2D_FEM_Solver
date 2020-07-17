#ifndef __TIME
#define __TIME
#include"hedder.hpp"

class TimeDepelopment{
    private:
        int NN, NE;
        double dt, convergence;
        std::vector<double> bar_M;

    public:
        TimeDepelopment(double delta_t, int init_NN, int init_NE, double con){
            dt = delta_t;
            NN = init_NN;
            NE = init_NE;
            convergence = con;
        }
        void make_M_approximately(std::vector<std::vector<double>> &M);
        void solve(std::vector<double> &p, std::vector<std::vector<double>> G, std::vector<double> R, std::vector<double> X, std::vector<double> Y, std::vector<int> NP1, std::vector<int> NP2, std::vector<int> NP3, std::vector<std::vector<double>> M);
        void output_pressure_vtk(std::vector<double> X, std::vector<double> Y, std::vector<int> NP1, std::vector<int> NP2, std::vector<int> NP3, std::vector<double> p, int i);
};
#endif