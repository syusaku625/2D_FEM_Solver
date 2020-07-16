#ifndef __PROCESS
#define __PROCESS
#include"hedder.hpp"

class PreProcess{
    private:
        std::vector<double> B1;
        std::vector<double> B2;
        std::vector<double> B3;
        std::vector<double> C1;
        std::vector<double> C2;
        std::vector<double> C3;
        std::vector<double> X1;
        std::vector<double> X2;
        std::vector<double> X3;
        std::vector<double> Y1;
        std::vector<double> Y2;
        std::vector<double> Y3;

    public:
        PreProcess(int NE){
            B1.resize(NE);
            B2.resize(NE);
            B3.resize(NE);
            C1.resize(NE);
            C2.resize(NE);
            C3.resize(NE);
            X1.resize(NE);
            X2.resize(NE);
            X3.resize(NE);
            Y1.resize(NE);
            Y2.resize(NE);
            Y3.resize(NE);
        }
        void make_stiffness_matrix(std::vector<std::vector<double>> &G, int NE, std::vector<int> NP1, std::vector<int> NP2, std::vector<int> NP3, std::vector<double> X, std::vector<double> Y);
        void set_dirichlet_boundary_condition(std::vector<std::vector<double>> &G, std::vector<double> &R, int NN, int NN2, int NN3, std::vector<int> IFIX_in, std::vector<int> IFIX_out, double in_pressure, double out_pressure);
        void return_B_vector(std::vector<double> &B_1, std::vector<double> &B_2, std::vector<double> &B_3);
        void return_C_vector(std::vector<double> &C_1, std::vector<double> &C_2, std::vector<double> &C_3);
        void return_element_center_of_gravity(std::vector<double> &E_G_X, std::vector<double> &E_G_Y);
};

#endif