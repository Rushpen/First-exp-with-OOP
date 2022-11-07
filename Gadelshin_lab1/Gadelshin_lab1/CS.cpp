#include <string>
#include "CS.h"
#include "Utils.h"

using namespace std;

int CS::max_idd = 0;

int CS::get_csid() { 
	return csid; 
}
int CS::up_csid() {
    return csid = ++max_idd;
}
void CS::set_csid(int i) {
	csid = i; 
}
int CS::get_w() {
	return workshops_num; 
}
int CS::get_w_r() { 
	return workshops_num_run; 
}
void CS::set_w_r(int a) {
	workshops_num_run = a; 
}

float CS::cs_unused() {
    return ((workshops_num - workshops_num_run) * 100 / (workshops_num));
}

void CS::show_cs(unordered_map<int, CS>& cs_map) {
    if (cs_map.size() != 0) {
        for (auto cs_m : cs_map)
            cout << cs_m.second;
    }
    else
        cout << "\nThere is no CS!" << endl;
}

istream& operator >> (istream& in, CS& cs) {
    cout << "\nIndex: " << cs.up_csid();
    cout << "\nName: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "\nNumber of workshops:";
    checking(cs.workshops_num);
    cout << "\nWorkshops at work: ";
    cs.workshops_num_run = get_correct(0, cs.workshops_num);
    cout << "\nEfficiency(0-100):" << endl;
    cs.efficiency = get_correct(0, 100);
    return in;
}
ostream& operator << (ostream& out, CS& cs)
{
    cout << "\nCS " << cs.csid << "\nname: " << cs.name << "\nnumber of workshops: "
        << cs.workshops_num << "\nworkshops at work: " << cs.workshops_num_run << endl;
    cout << "efficiency: " << cs.efficiency << "%" << endl;

    return out;
}
ofstream& operator << (ofstream& fcout, CS& cs) {
    fcout << cs.csid << "\n" << cs.name << "\n" << cs.workshops_num << "\n" << cs.workshops_num_run
        << "\n" << cs.efficiency << endl;
    return fcout;
}
ifstream& operator >> (ifstream& fcin, CS& cs) {
    fcin >> cs.csid;
    fcin.ignore();
    getline(fcin, cs.name);
    fcin >> cs.workshops_num >> cs.workshops_num_run >> cs.efficiency;
    return fcin;
}