#include "Pipe.h"
#include "Utils.h"

using namespace std;

int Pipe::max_id = 0;

int Pipe::get_pid() {
    return pid; 
}
int Pipe::up_pid() {
    return pid = ++max_id;
}
void Pipe::set_pid(int i) {
    pid = i;
}
bool Pipe::get_stat() {
    return status;
}
void Pipe::set_stat(bool a) {
    status = a; 
}

void Pipe::p_status(bool status_p)
{
    if (status_p == false) {
        cout << "status: Pipe in repair\n";
    }
    else {
        cout << "status: Pipe is ready for operation\n";
    }
}

void Pipe::show_pipe(unordered_map <int, Pipe>& p_map) {
    if (p_map.size() != 0) {
        for (auto p_m : p_map)
            cout << p_m.second;
    }
    else
        cout << "\nThere is no pipe!" << endl;
}

istream& operator >> (istream& in, Pipe& p) 
{
    cout << "\nIndex: " << p.up_pid();
    cout << "\nName: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, p.name);
    cout << "\nLenght: ";
    checking(p.lenght);
    cout << "\nDiameter: ";
    checking(p.diam);
    cout << "\n Choose pipe status:\n 0.In repair\n 1.In work\n ";
    p.status = get_correct(0, 1);
    p.p_status(p.status);
    return in;
}
ostream& operator << (ostream& out, Pipe& p)
{
    cout << "\nPipe " << p.pid << "\nname: " << p.name << "\nlenght: "
        << p.lenght << "\ndiameter: " << p.diam << endl;
    p.p_status(p.status);
    return out;
}
ofstream& operator << (ofstream& fcout, Pipe& p) {
    fcout << p.pid << "\n" << p.name << "\n" << p.lenght
        << "\n" << p.diam << "\n" << p.status << endl;
    return fcout;
}
ifstream& operator >> (ifstream& fcin, Pipe& p) {
    fcin >> p.pid;
    fcin.ignore();
    getline(fcin, p.name);
    fcin >> p.lenght >> p.diam >> p.status;
    return fcin;
}
