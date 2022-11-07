#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

class CS
{
private:
    int csid=0;
    int workshops_num, workshops_num_run;
    float efficiency;
public:
    std::string name = "";
    static int max_idd;

    int get_csid();
    int up_csid();
    void set_csid(int i);
    int get_w();
    int get_w_r();
    void set_w_r(int a);
    void show_cs(unordered_map<int, CS>& cs_map);

    float cs_unused();

    friend istream& operator >> (istream& in, CS& cs);
    friend ostream& operator << (ostream& out, CS& cs);
    friend ofstream& operator << (ofstream& fcout, CS& cs);
    friend ifstream& operator >> (ifstream& fcin, CS& cs);
};

