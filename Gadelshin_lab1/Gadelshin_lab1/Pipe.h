#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;
class Pipe
{
private:
    int pid=0;
    float lenght, diam;
    bool status;

public:
    string name = "";
    static int max_id;

    int get_pid();
    int up_pid();
    void set_pid(int i);
    bool get_stat();
    void set_stat(bool a);

    void show_pipe(unordered_map <int, Pipe>& p_map);
    void p_status(bool status);

    friend istream& operator >> (istream& in, Pipe& p);
    friend ostream& operator << (ostream& out, Pipe& p);
    friend ofstream& operator << (ofstream& fcout, Pipe& p);
    friend ifstream& operator >> (ifstream& fcin, Pipe& p);

};

