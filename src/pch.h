#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <fstream>
#include<string.h>
#ifndef PCH_H
#define PCH_H


#include "framework.h"

#endif 

#ifdef IMPORT_DLL
#else
#define IMPORT_DLL _declspec(dllimport) 
#endif
IMPORT_DLL std::set<std::pair<double,double>> solve(std::vector<std::pair<char, std::pair<std::pair<int, int>, std::pair<int, int>>>> line, std::vector<std::pair<char, std::pair<std::pair<int, int>, int>>> circle);
IMPORT_DLL bool if_line_same(std::pair<std::pair<double, double>, std::pair<double, double>> a, std::pair<std::pair<double, double>, std::pair<double, double>> b);
IMPORT_DLL bool if_circle_same(std::pair<std::pair<double, double>, double> c1, std::pair<std::pair<double, double>, double> c2);
IMPORT_DLL std::set<std::pair<double, double>> input_line(std::pair<std::pair<double, double>, std::pair<double, double>> line1);
IMPORT_DLL std::set<std::pair<double, double>> input_ray(std::pair<std::pair<double, double>, std::pair<double, double>> ray1);
IMPORT_DLL std::set<std::pair<double, double>> input_segment(std::pair<std::pair<double, double>, std::pair<double, double>> segment1);
IMPORT_DLL std::set<std::pair<double, double>> input_circle(std::pair<std::pair<double, double>, double> circle1);
IMPORT_DLL long main1(int argc, char* argv[]);