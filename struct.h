#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Visits{
    string date_visit;
    string time_visit;
    string diagnos;
    string recomendations;
    string doctor_lastname;
    string doctor_inicial;
};

struct Student{
string lastname;
string inicial;
int date_born; 
string phone_number;
int join_date;
string group_name;
string university;
string cafedra;
vector<Visits> visits;
};

#endif