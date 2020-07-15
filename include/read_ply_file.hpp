#ifndef __PLYREAD
#define __PLYREAD
#include"hedder.hpp"
class Read_Ply
{
    private:
        std::string buf_1, buf_2;
        int node_quantity;
        int element_quantity;
        std::vector<double> x_c, y_c, z_c;
        std::vector<std::vector<int>> element_c;
        double min_x, max_x, min_y, max_y;

    public:
        Read_Ply(){
            min_x = 10000.0;
            max_x = 0.0;
            min_y = 10000.0;
            max_y = 0.0;
        }
        int read_ply(std::string file);
        int get_total_number_of_node();
        void get_node_number(std::vector<int> &NP1, std::vector<int> &NP2, std::vector<int> &NP3);
        void get_node_coordinator(std::vector<double> &X, std::vector<double> &Y);
        int get_total_number_of_element();
        int get_Dirichlet_boundary_node_quantity(std::string judge);
        void get_Dirichlet_boundary_node_number(std::string judge, std::vector<int> &IFIX);
};

#endif