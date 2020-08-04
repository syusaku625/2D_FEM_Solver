#include"validation.hpp"
#include"hedder.hpp"
using namespace std;

void Validation::caluculate_l2_nolmu(int NN, vector<double> X, vector<double> Y, vector<double> p, vector<double> &ans){
    double L2=0.0;
    for (int i = 0; i < p.size(); i++){
        double ans_t = 0.0;
        for (double j = 1; j <= 5; j+=2){
            ans_t += (exp(-j * M_PI * (Y[i] + 12.499) / 25.0) * sin(j * M_PI * (X[i] + 12.499) / 25.0))/j;
        }
        ans_t *= (4.0 * 1.0 / M_PI);
        cout << ans_t << endl;
        ans.push_back(ans_t);
        L2 += fabs(ans_t - p[i]) * fabs(ans_t - p[i]);
    }
    L2 = sqrt(L2);
    cout << "L2" << " " << L2 << endl;
    cout << NN << endl;
}
void Validation::pressure_output(int NN, int NE, vector<double> X, vector<double> Y, vector<int> NP1, vector<int> NP2, vector<int> NP3, vector<double> p, vector<double> ans){
    ofstream output("result/result_s.vtk");
    ofstream output_3("result/theory_pressure.dat");
    ofstream output_x("result/x_coordinator.dat");
    vector<pair<double, double>> theory_output;
    for (int i = 0; i < NN; i++){
        if(fabs(Y[i])<=0.001){
            theory_output.push_back(make_pair(X[i], ans[i]));
        }
    }
    sort(theory_output.begin(), theory_output.end());
    for (int i = 0; i < theory_output.size(); i++){
        output_3 << theory_output[i].second << endl;
    }
    for (int i = 0; i < theory_output.size(); i++){
        output_x << theory_output[i].first << endl;
    }
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
        output << ans[i] << endl;
    }
}