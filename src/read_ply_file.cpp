#include"read_ply_file.hpp"
#include"hedder.hpp"
using namespace std;

int Read_Ply::read_ply(string file){
    ifstream read(file);
    if(read.fail()){
        cout << "Faild open file !!" << endl;
        exit(1);
    }
    for (int i = 0; i < 4; i++){
        getline(read, buf_1);
    }
    read >> buf_1 >> buf_2 >> node_quantity;
    for (int i = 0; i < 4; i++){
        getline(read, buf_1);
    }
    read >> buf_1 >> buf_2 >> element_quantity;
    cout << node_quantity << " " << element_quantity << endl;
    while(!(buf_1=="end_header")){
        getline(read, buf_1);
    }
    
    for (int i = 0; i < node_quantity; i++){
        double x, y, z;
        read >> x >> y >> z;
        min_x = min(min_x, x);
        min_y = min(min_y, y);
        max_x = max(max_x, x);
        max_y = max(max_y, y);
        x_c.push_back(x);
        y_c.push_back(y);
        z_c.push_back(z);
    }
    //cout << x_c[0] << " " << y_c[0] << " " << z_c[0] << endl;
    cout << x_c[x_c.size()-1] << " " << y_c[y_c.size()-1] << " " << z_c[z_c.size()-1] << endl;
    vector<int> element_number;
    element_c.resize(element_quantity);
    for (int i = 0; i < element_quantity; i++){
        int e_1, e_2, e_3, dammy;
        element_number.push_back(i);
        read >> dammy >> e_1 >> e_2 >> e_3;
        //cout << e_1 << " " << e_2 << " " << e_3 << endl;
        element_c[i].push_back(e_1);
        element_c[i].push_back(e_2);
        element_c[i].push_back(e_3);
    }
    //cout << element_number[0] << " " << element_c[0][0] << " " << element_c[0][1] << " " << element_c[0][2] << endl;
    //cout << element_number[element_number.size()-1] << " " << element_c[element_c.size()-1][0] << " " << element_c[element_c.size()-1][1] << " " << element_c[element_c.size()-1][2] << endl;
    return 1;
}
int Read_Ply::get_total_number_of_node(){
    return node_quantity;
}

void Read_Ply::get_node_number(vector<int> &NP1, vector<int> &NP2, vector<int> &NP3){
    for (int i = 0; i < element_quantity; i++){
        NP1.push_back(element_c[i][0]);
        NP2.push_back(element_c[i][1]);
        NP3.push_back(element_c[i][2]);
    }
}

void Read_Ply::get_node_coordinator(vector<double> &X, vector<double> &Y){
    for (int i = 0; i < node_quantity; i++){
        X.push_back(x_c[i]);
        Y.push_back(y_c[i]);
    }
}

int Read_Ply::get_total_number_of_element(){
    return element_quantity;
}

void Read_Ply::get_Dirichlet_boundary_node_number(string judge, std::vector<int> &IFIX){
    if (judge == "x_min"){
        for (int i = 0; i < node_quantity; i++){
            if(fabs(x_c[i]-min_x)<0.01){
                IFIX.push_back(i);
            }
        }
    }
    else if(judge=="y_min"){
        for (int i = 0; i < node_quantity; i++){
            if(fabs(y_c[i]-min_y)<0.01){
                IFIX.push_back(i);
            }
        }
    }
    else if(judge=="x_max"){
        for (int i = 0; i < node_quantity; i++){
            if(fabs(x_c[i]-max_x)<0.01){
                IFIX.push_back(i);
            }
        }
    }
    else if(judge=="y_max"){
        for (int i = 0; i < node_quantity; i++){
            if(fabs(y_c[i]-max_x)<0.01){
                IFIX.push_back(i);
            }
        }
    }
    else{
        cout << "Boundary condition setting error !!" << endl;
        exit(1);
    }
}

int Read_Ply::get_Dirichlet_boundary_node_quantity(string judge){
    int boundary_node_quantity = 0;
    if (judge == "x_min"){
        for (int i = 0; i < node_quantity; i++){
            if(fabs(x_c[i]-min_x)<0.01){
                boundary_node_quantity++;
            }
        }
    }
    else if(judge=="y_min"){
        for (int i = 0; i < node_quantity; i++){
            if(fabs(y_c[i]-min_y)<0.01){
                boundary_node_quantity++;
            }
        }
    }
    else if(judge=="x_max"){
        for (int i = 0; i < node_quantity; i++){
            if(fabs(x_c[i]-max_x)<0.01){
                boundary_node_quantity++;
            }
        }
    }
    else if(judge=="y_max"){
        for (int i = 0; i < node_quantity; i++){
            if(fabs(y_c[i]-max_x)<0.01){
                boundary_node_quantity++;
            }
        }
    }
    else{
        cout << "Boundary condition setting error !!" << endl;
        return -1;
    }
    return boundary_node_quantity;
}