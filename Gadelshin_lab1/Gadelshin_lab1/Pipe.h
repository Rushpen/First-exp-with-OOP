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
    int get_pid() { return pid; }
    int up_pid() { return pid = ++max_id; }
    void set_pid(int i) { pid = i; }
    void set_stat(bool a) { status = a; }
    bool get_stat() { return status; }

    void show_pipe(unordered_map <int, Pipe>& p_map);
    void p_status(bool status);

    friend istream& operator >> (istream& in, Pipe& p);
    friend ostream& operator << (ostream& out, Pipe& p);
    friend ofstream& operator << (ofstream& fcout, Pipe& p);
    friend ifstream& operator >> (ifstream& fcin, Pipe& p);
};

