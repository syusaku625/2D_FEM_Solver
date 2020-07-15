#include"hedder.hpp"
#include"output_vtk.hpp"
using namespace std;
void output::output_vtk(int NN, int NE, vector<double> X, vector<double> Y, vector<int> NP1, vector<int> NP2, vector<int> NP3, vector<double> p){
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