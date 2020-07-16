#include"hedder.hpp"
#include"fem_preprocess.hpp"
using namespace std;

void PreProcess::make_stiffness_matrix(vector<vector<double>> &G, int NE, vector<int> NP1, vector<int> NP2, vector<int> NP3, vector<double> X, vector<double> Y){
    for (int i = 0; i < NE; i++)
    {
        int N1 = NP1[i];
        int N2 = NP2[i];
        int N3 = NP3[i];
        X1[i] = X[N1];
        X2[i] = X[N2];
        X3[i] = X[N3];
        Y1[i] = Y[N1];
        Y2[i] = Y[N2];
        Y3[i] = Y[N3];
        double delta2 = X1[i] * (Y2[i] - Y3[i]) + X2[i] * (Y3[i] - Y1[i]) + X3[i] * (Y1[i] - Y2[i]);
        double delta = delta2 * 0.5;
        delta2 = 1.0 / delta2;
        B1[i] = (Y2[i] - Y3[i]) * delta2;
        B2[i] = (Y3[i] - Y1[i]) * delta2;
        B3[i] = (Y1[i] - Y2[i]) * delta2;
        C1[i] = (X3[i] - X2[i]) * delta2;
        C2[i] = (X1[i] - X3[i]) * delta2;
        C3[i] = (X2[i] - X1[i]) * delta2;
        G[N1][N1] = (B1[i] * B1[i] + C1[i] * C1[i]) * delta + G[N1][N1];
        G[N2][N1] = (B2[i] * B1[i] + C2[i] * C1[i]) * delta + G[N2][N1];
        G[N3][N1] = (B3[i] * B1[i] + C3[i] * C1[i]) * delta + G[N3][N1];
        G[N1][N2] = (B1[i] * B2[i] + C1[i] * C2[i]) * delta + G[N1][N2];
        G[N2][N2] = (B2[i] * B2[i] + C2[i] * C2[i]) * delta + G[N2][N2];
        G[N3][N2] = (B3[i] * B2[i] + C3[i] * C2[i]) * delta + G[N3][N2];
        G[N1][N3] = (B1[i] * B3[i] + C1[i] * C3[i]) * delta + G[N1][N3];
        G[N2][N3] = (B2[i] * B3[i] + C2[i] * C3[i]) * delta + G[N2][N3];
        G[N3][N3] = (B3[i] * B3[i] + C3[i] * C3[i]) * delta + G[N3][N3];
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

void PreProcess::return_B_vector(vector<double> &B_1, vector<double> &B_2, vector<double> &B_3){
    for (int i = 0; i < B1.size(); i++){
        B_1[i] = B1[i];
        B_2[i] = B2[i];
        B_3[i] = B3[i];
    }
}

void PreProcess::return_C_vector(vector<double> &C_1, vector<double> &C_2, vector<double> &C_3){
    for (int i = 0; i < C1.size(); i++){
        C_1[i] = C1[i];
        C_2[i] = C2[i];
        C_3[i] = C3[i];
    }
}

void PreProcess::return_element_center_of_gravity(vector<double> &E_G_X, vector<double> &E_G_Y){
    for (int i = 0; i < B1.size(); i++){
        E_G_X[i] = (X1[i] + X2[i] + X3[i]) / 3.0;
        E_G_Y[i] = (Y1[i] + Y2[i] + Y3[i]) / 3.0;
    }
}