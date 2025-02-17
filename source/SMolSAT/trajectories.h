/*Soft-Matter Molecular Simulation Analysis Toolkit (SMolSAT)*/
/*Written by Zhenghao Wu, modified from AMDAT written by David S. Simmons*/
#include <vector>
#include <iostream>

#include "system.h"
#include "analysis_base.h"
#include "multibody_list.h"
#include "vector_map.h"
#include "trajectory_list.h"
#include "multibody_list.h"
#include "static_trajectory_list.h"
#include "value_list.h"

#include "../extern/pybind11/include/pybind11/pybind11.h"

#ifndef CREATE_LIST
#define CREATE_LIST

class PYBIND11_EXPORT Trajectories
{   
    private:
    //list of particle lists
    int n_gaussian_comparisons = 0;
    int vhs_defined = 0;
    int n_trajectory_list_bins = 0;
    std::shared_ptr<System> analyte;

    public:
    Trajectories(std::shared_ptr<System> sys);

    void initialize_lists();
    /*Methods to handle value lists*/
    Vector_Map<string,Value_List<float>*> value_lists;
    Value_List<float>* find_value_list(string,bool allow_nofind=0)const;
    void add_value_list(Value_List<float>*, string);
    void delete_value_list(string);

    /*Members to store and access trajectory_list objects*/
    Vector_Map <string, Trajectory_List*> trajectories;
    Trajectory_List* find_trajectorylist(string, bool allow_nofind=0)const;
    void add_trajectorylist(Trajectory_List*, string);
    void combine_trajectories(string newlistname, vector<string> listnames);
    void delete_trajectory_list(string listname);

    /*Members to store and access multibody_list objects*/
    Vector_Map<string,Multibody_List*> multibody_lists;
    Multibody_List* find_multibody_list(string,bool allow_nofind=0)const;
    void add_multibody_list(Multibody_List*,string);
    void delete_multibody_list(string listname);
    void combine_multibody_lists(string newlistname, vector<string> listnames);
    void delete_multibodies(string listname);

    void create_list(string listname, string args);
    void create_multibodies(string listname, string trajectory_type_name, string centertypename, string args);
};

void export_Trajectories(pybind11::module& m);

#endif