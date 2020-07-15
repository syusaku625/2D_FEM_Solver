#include"hedder.hpp"
#include"read_ply_file.hpp"
#include"output_vtk.hpp"
#include"equation_solver.hpp"
#include"fem_preprocess.hpp"
using namespace std;
int main()
{
    Read_Ply read;
    string set_boundary_in="x_min";
    string set_boundary_out = "x_max";
    double in_pressure = 100.0;
    double out_pressure = 0.0;
    double convergence = 0.001;
    read.read_ply("ply_data/fem_mesh_data.ply");
    int NN, NE, NN2, NN3;
    vector<int> NP1, NP2, NP3, IFIX_in, IFIX_out;
    vector<double> X, Y;
    NN = read.get_total_number_of_node();
    NE = read.get_total_number_of_element();
    read.get_node_number(NP1, NP2, NP3);
    read.get_node_coordinator(X, Y);
    NN2=read.get_Dirichlet_boundary_node_quantity(set_boundary_in);
    NN3 = read.get_Dirichlet_boundary_node_quantity(set_boundary_out);
    read.get_Dirichlet_boundary_node_number(set_boundary_in, IFIX_in);
    read.get_Dirichlet_boundary_node_number(set_boundary_out, IFIX_out);
    vector<vector<double>> G(NN, vector<double>(NN));
    vector<double> R(NN);
    vector<double> p(NN);
    PreProcess preprocess;
    preprocess.make_stiffness_matrix(G, NE, NP1, NP2, NP3, X, Y);
    preprocess.set_dirichlet_boundary_condition(G, R, NN, NN2, NN3, IFIX_in, IFIX_out, in_pressure, out_pressure);
    Solver solver;   
    solver.Jacobi_method(p, R, G, NN, convergence);
    output OUT;
    OUT.output_vtk(NN, NE, X, Y, NP1, NP2, NP3, p);
}