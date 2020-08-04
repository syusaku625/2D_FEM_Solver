#ifndef __VALID
#define __VALID
#include"hedder.hpp"
class Validation{
    private:
    public:
        void caluculate_l2_nolmu(int NN, std::vector<double> X, std::vector<double> Y, std::vector<double> p, std::vector<double> &ans);
        void pressure_output(int NN, int NE, std::vector<double> X, std::vector<double> Y, std::vector<int> NP1, std::vector<int> NP2, std::vector<int> NP3, std::vector<double> p, std::vector<double> ans);
};
#endif
