#include"hedder.hpp"
#include"read_ply_file.hpp"
#include"output_vtk.hpp"
#include"equation_solver.hpp"
#include"fem_preprocess.hpp"
#include"time_problem.hpp"
using namespace std;
int main()
{
    Read_Ply read;
    string set_boundary_in="x_min";
    string set_boundary_out = "x_max";
    double in_pressure = 100.0;
    double out_pressure = 0.0;
    double convergence = 0.001;
    double delta_t = 0.001;
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
    vector<vector<double>> M(NN, vector<double>(NN));
    vector<double> R(NN);
    vector<double> B1(NE), B2(NE), B3(NE);
    vector<double> C1(NE), C2(NE), C3(NE);
    vector<double> G_X(NE),G_Y(NE);
    vector<double> p(NN);
    vector<double> vx(NE), vy(NE);
    PreProcess preprocess(NE);
    preprocess.make_stiffness_matrix(G, NE, NP1, NP2, NP3, X, Y);
    preprocess.set_dirichlet_boundary_condition(G, R, NN, NN2, NN3, IFIX_in, IFIX_out, in_pressure, out_pressure);
    preprocess.make_M_matrix(M, NE, NP1, NP2, NP3);    
    TimeDepelopment time_solve(delta_t, NN, NE, convergence);
    //time_solve.make_M_approximately(M);
    time_solve.solve(p, G, R, X, Y, NP1, NP2, NP3,M);

    //preprocess.return_B_vector(B1, B2, B3);
    //preprocess.return_C_vector(C1, C2, C3);

    //preprocess.return_element_center_of_gravity(G_X, G_Y);
    //Solver solver;
    //solver.Jacobi_method(p, R, G, NN, convergence);
    //output OUT;
    //OUT.output_pressure_vtk(NN, NE, X, Y, NP1, NP2, NP3, p);
    //OUT.calculate_velocity(NE, vx, vy, B1, B2, B3, C1, C2, C3, p, NP1, NP2, NP3);
    //OUT.output_velocity_vtk(NE, vx, vy, G_X, G_Y);
}