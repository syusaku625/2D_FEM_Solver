#include"hedder.hpp"
#include"time_problem.hpp"
using namespace std;

void TimeDepelopment::make_M_approximately(vector<vector<double>> &M){
    bar_M.resize(NN);
    for (int i = 0; i < NN; i++){
        double sum = 0;
        for (int j = 0; j < NN; j++){
            sum += M[i][j];
        }
        sum = 1.0 / sum;
       // cout << sum << endl;
        bar_M.push_back(sum);
    }
}

void TimeDepelopment::solve(vector<double> &p, vector<vector<double>> G, vector<double> R, vector<double> X, vector<double> Y, vector<int> NP1, vector<int> NP2, vector<int> NP3, vector<vector<double>> M){
    cout << bar_M.size() << endl;
    for (int i = 0; i < NN; i++)
    {
        double sum = 0;
        for (int j = 0; j < NN; j++){
            sum += M[i][j];
        }
        sum = 1.0 / sum;
        bar_M.push_back(sum);
    }
    int count = 0;
    while (1)
    {
        vector<double> tmp(NN);
        for (int i = 0; i < NN; i++){
            for (int j = 0; j < NN; j++){
                tmp[i] += G[i][j] * p[j];
            }
        }
        for (int i = 0; i < NN; i++){
            tmp[i] -= R[i];
            tmp[i] *= bar_M[i];
            tmp[i] *= dt;
        }
        for (int i = 0; i < NN; i++){
            tmp[i] = p[i] - tmp[i];
        }
        output_pressure_vtk(X, Y, NP1, NP2, NP3, p, count);
        count++;
        double err = 0.0;
        for (int i = 0; i < NN; i++){
            err += fabs(tmp[i] - p[i]);
            p[i] = tmp[i];
        }
        cout << "err" << " " << err << endl;
        if (err < convergence){
            break;
        }
    }
}

void TimeDepelopment::output_pressure_vtk(vector<double> X, vector<double> Y, vector<int> NP1, vector<int> NP2, vector<int> NP3, vector<double> p, int i){
     stringstream filename;
     filename << "pressure" << i << ".vtk";
     string result = "result/"+filename.str();
     ofstream output;
     output.open(result.c_str());
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
