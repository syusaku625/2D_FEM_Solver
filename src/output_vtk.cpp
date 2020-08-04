#include"hedder.hpp"
#include"output_vtk.hpp"
using namespace std;

void output::output_pressure_vtk(int NN, int NE, vector<double> X, vector<double> Y, vector<int> NP1, vector<int> NP2, vector<int> NP3, vector<double> p){
    ofstream output_2("result/pressure.dat");
    vector<pair<double, double>> pressure_output;
    for (int i = 0; i < NN; i++){
        if(fabs(Y[i])<=0.001){
            pressure_output.push_back(make_pair(X[i], p[i]));
        }
    }
    sort(pressure_output.begin(), pressure_output.end());
    for (int i = 0; i < pressure_output.size(); i++){
        output_2 << pressure_output[i].second << endl;
    }
    ofstream output("result/result.vtk");
    output << "# vtk DataFile Version 3.0" << endl;
    output << "pressure" << endl;
    output << "ASCII" << endl;
    output << "DATASET UNSTRUCTURED_GRID" << endl;
    output << "POINTS" << " " << NN << " " << "float" << endl;
    for (int i = 0; i < NN; i++){
        output << X[i] << " " << Y[i] << " " << 0.0 << endl;
    }
    output << "CELLS" << " " << NE << " " << 4*NE << endl;
    for (int i = 0; i < NE; i++){
        output << 3 << " " << NP1[i] << " " << NP2[i] << " " << NP3[i] << endl;
    }
    output << "CELL_TYPES" << " " << NE << endl;
    for (int i = 0; i < NE; i++){
        output << 5 << endl;
    }
    output << "POINT_DATA" << " " << NN << endl;
    output << "SCALARS" << " " << "pressure" << " " << "double" << endl;
    output << "LOOKUP_TABLE" << " " << "default" << endl;
    for (int i = 0; i < NN; i++){
        output << p[i] << endl;
    }
}

void output::calculate_velocity(int NE, vector<double> &vx, vector<double> &vy, vector<double> B1, vector<double> B2, vector<double> B3, vector<double> C1, vector<double> C2, vector<double> C3, vector<double> p, vector<int> N1, vector<int> N2, vector<int> N3){
    for (int i = 0; i < NE; i++){
        vx[i] = B1[i] * p[N1[i]] + B2[i] * p[N2[i]] + B3[i] * p[N3[i]];
        vy[i] = C1[i] * p[N1[i]] + C2[i] * p[N2[i]] + C3[i] * p[N3[i]];
    }
}

void output::output_velocity_vtk(int NE, vector<double> vx, vector<double> vy, vector<double> G_X, vector<double> G_Y){
    ofstream output("result/velocity.vtk");
    output << "# vtk DataFile Version 3.0" << endl;
    output << "velocity" << endl;
    output << "ASCII" << endl;
    output << "DATASET UNSTRUCTURED_GRID" << endl;
    output << "POINTS" << " " << NE << " " << "float" << endl;
    for (int i = 0; i < NE; i++){
        output << G_X[i] << " " << G_Y[i] << " " << 0.0 << endl;
    }
    output << "POINT_DATA" << " " << NE << endl;
    output << "VECTORS" << " " << "velocity" << " " << "double" << endl;
    for (int i = 0; i < NE; i++){
        output << -vx[i] << " " << -vy[i] << " " << 0.0 << endl;
    }
}