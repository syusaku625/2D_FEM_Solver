#include"equation_solver.hpp"
#include"hedder.hpp"
using namespace std;

void Solver::Jacobi_method(std::vector<double> &p, vector<double> &R, vector<vector<double>> &G, int NN, double convergence){
    while(1){
        tmp_p.resize(NN);
        for (int i = 0; i < NN; i++)
        {
            tmp_p[i]=R[i];
            for (int j = 0; j < NN; j++){
                if(i!=j){
                    tmp_p[i] -= G[i][j] * tmp_p[j];
                }
            }
            tmp_p[i] /= G[i][i];
        }
        double err = 0.0;
        for (int i = 0; i < NN; i++){
            err += fabs(tmp_p[i] - p[i]);
            p[i] = tmp_p[i];
        }
        cout << "err" << " " << err << endl;
        if (err < convergence){
            break;
        }
    }
}