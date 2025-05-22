#ifndef FUNC_H
#define FUNC_H
#include <iostream>
#include <string>
#include <vector>
#include "classList.h"
#include "des_utils.h"
#include <sstream>
#include <fstream>
#include <string.h>
#include <limits>
using namespace std; 

vector<std::string> readLineAsStrings(string line);
void clear_key(DES_cblock& key);
string readFile(const string& filename);
void writeFile(const string& filename, const string& content);
void ShowFile(const string& filename);
void des_menu();
void handleStudentInput(Student& student);
void handleVisitInput(Visits& visit);

#endif