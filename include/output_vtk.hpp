#ifndef __OUTPUT
#define __OUTPUT
#include"hedder.hpp"
class output
{
    private:

    public:
        void output_vtk(int NN, int NE, std::vector<double> X, std::vector<double> Y, std::vector<int> NP1, std::vector<int> NP2, std::vector<int> NP3, std::vector<double> p);
};

#endif