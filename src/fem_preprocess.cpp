#include"hedder.hpp"
#include"fem_preprocess.hpp"
using namespace std;

void PreProcess::make_stiffness_matrix(vector<vector<double>> &G, int NE, vector<int> NP1, vector<int> NP2, vector<int> NP3, vector<double> X, vector<double> Y){
    for (int i = 0; i < NE; i++)
    {
        int N1 = NP1[i];
        int N2 = NP2[i];
        int N3 = NP3[i];
        double X1 = X[N1];
        double X2 = X[N2];
        double X3 = X[N3];
        double Y1 = Y[N1];
        double Y2 = Y[N2];
        double Y3 = Y[N3];
        double delta2 = X1 * (Y2 - Y3) + X2 * (Y3 - Y1) + X3 * (Y1 - Y2);
        double delta = delta2 * 0.5;
        delta2 = 1.0 / delta2;
        double B1 = (Y2 - Y3) * delta2;
        double B2 = (Y3 - Y1) * delta2;
        double B3 = (Y1 - Y2) * delta2;
        double C1 = (X3 - X2) * delta2;
        double C2 = (X1 - X3) * delta2;
        double C3 = (X2 - X1) * delta2;
        G[N1][N1] = (B1 * B1 + C1 * C1) * delta + G[N1][N1];
        G[N2][N1] = (B2 * B1 + C2 * C1) * delta + G[N2][N1];
        G[N3][N1] = (B3 * B1 + C3 * C1) * delta + G[N3][N1];
        G[N1][N2] = (B1 * B2 + C1 * C2) * delta + G[N1][N2];
        G[N2][N2] = (B2 * B2 + C2 * C2) * delta + G[N2][N2];
        G[N3][N2] = (B3 * B2 + C3 * C2) * delta + G[N3][N2];
        G[N1][N3] = (B1 * B3 + C1 * C3) * delta + G[N1][N3];
        G[N2][N3] = (B2 * B3 + C2 * C3) * delta + G[N2][N3];
        G[N3][N3] = (B3 * B3 + C3 * C3) * delta + G[N3][N3];
    }
}
void PreProcess::set_dirichlet_boundary_condition(vector<vector<double>> &G, vector<double> &R, int NN, int NN2, int NN3, vector<int> IFIX_in, vector<int> IFIX_out, double in_pressure, double out_pressure){
    for (int i = 0; i < NN2; i++)
    {
        int IK = IFIX_in[i];
        for (int j = 0; j < NN; j++){
            G[IK][j] = 0.0;
        }
        G[IK][IK] = 1.0;
        R[IK] = in_pressure;
    }
    for (int i = 0; i < NN3; i++){
        int IK = IFIX_out[i];
        for (int j = 0; j < NN; j++){
            G[IK][j] = 0.0;
        }
        G[IK][IK] = 1.0;
        R[IK] = out_pressure;
    }
}