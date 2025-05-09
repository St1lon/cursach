#ifndef STRUCT_H
#define STRUCT_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Person{
    public:
    string lastname;
    string inicial;
    int date_born; 
    string phone_number;
    virtual Person* clone() const = 0;
};
class Visits{
public:
    string date_visit;
    string time_visit;
    string diagnos;
    string recomendations;
    string doctor_lastname;
    string doctor_inicial;
};

class Student : public Person{
public:
int join_date;
string group_name;
string university;
string cafedra;
vector<Visits> visits;
Person* clone() const override {
return new Student(*this);
}
};
#endif