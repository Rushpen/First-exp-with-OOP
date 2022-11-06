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

void CS::show_cs(unordered_map<int, CS>& cs_map) {
    if (cs_map.size() != 0) {
        for (auto cs_m : cs_map)
            cout << cs_m.second;
    }
    else
        cout << "\nThere is no CS!" << endl;
}

unordered_set <int> CS::Cs_filter(unordered_map<int, CS>& cs_map) {
    int a;
    unordered_set<int> new_cs;
    if (cs_map.size() != 0)
    {
        cout << "Choose filter:  0.By name 1.By percentage of unused works' " << endl;
        a = get_correct(0, 1);
        if (a == 0)
        {
            string n;
            cout << "Input name: " << endl;
            cin >> n;
            for (auto cst : cs_map)
            {
                if (cst.second.name.find(n) != string::npos)
                    new_cs.insert(cst.first);
            }
        }
        else if (a == 1)
        {
            float per, t;
            cout << "Input percentage of unused works(0-100): " << endl;
            per = get_correct(0, 100);
            for (auto cst : cs_map)
            {
                t = ((cst.second.get_w() - cst.second.get_w_r()) * 100 / (cst.second.get_w()));
                if ((per > t - 5) & (per < t + 5))
                    new_cs.insert(cst.first);
            }
        }
        if (new_cs.size() == 0)
            cout << "\nThere are no such CSs!" << endl;
    }
    else
        cout << "\nCSs not yet avalaible or have been deleted" << endl;
    for (auto& v : new_cs)
        cout << cs_map[v];
    return new_cs;
}


void CS::edit_cs(unordered_map<int, CS>& cs_map) {
    int b = 0, ed, id;
    bool d;
    unordered_set<int>idcs;
    if (cs_map.size() != 0)
    {
        cout << "\nChange: 1.Edit one CS  2.Edit >1 CS  0.Delete CS" << endl;
        ed = get_correct(0, 2);
        if (ed == 1) {
            cout << "Enter index of CS: ";
            id = id_check(cs_map);
            cout << "\n Input new number of workshops at work: \n ";
            auto cs = cs_map.find(id);
            b = get_correct(0, cs_map.at(id).get_w());
            cs_map.at(id).set_w_r(b);
            cout << "\nChanges applied" << endl;
        }

        if (ed == 2) {
            cout << "Choose method: 0.By ids  1.By filter" << endl;
            d = get_correct(0, 1);
            if (d == 0) {
                int n, z;
                cout << "How many CSs you want to edit?" << endl;
                n = get_correct(1, int(cs_map.size()));
                cout << "Input numbers of CSs: " << endl;
                for (int i = 0; i < n; ++i) {
                    z = get_correct(1, int(cs_map.size()));
                    if (cs_map.find(z) != cs_map.end())
                        idcs.insert(z);
                }
                cout << "\nInput new number of working workshops: " << endl;
                for (auto& ci : idcs) {
                    b = get_correct(0, cs_map[ci].get_w());
                    cs_map.at(ci).set_w_r(b);
                }
                cout << "\nChanges applied" << endl;
            }
            if (d == 1) {
                idcs = Cs_filter(cs_map);
                if (idcs.size() != 0) {
                    cout << "\nInput new number of working works" << endl;
                    for (auto& ci : idcs) {
                        b = get_correct(0, cs_map[ci].get_w());
                        cs_map.at(ci).set_w_r(b);
                    }
                    cout << "\nChanges applied" << endl;
                }
            }
        }

        else if (ed == 0) {
            delete_css(cs_map);
        }
    }
    else
        cout << "There is no CS for edit!" << endl;
}

void CS::delete_css(unordered_map<int, CS>& cs_map) {
    int id, h;
    bool ed;
    unordered_set<int>ids;
    cout << "Delete: 0.One cs  1.CSs" << endl;
    ed = get_correct(0, 1);
    if (ed == 0) {
        cout << "Input index of CS: " << endl;
        id = id_check(cs_map);
        auto pipe = cs_map.find(id);
        cs_map.erase(pipe);
        cout << "\nPipe deleted" << endl;
    }
    if (ed == 1) {
        bool a;
        cout << "0.By ids  1.By filter" << endl;
        h = get_correct(0, 1);
        if (h == 0) {
            int n, z;
            cout << "How many pipes you want to delete?" << endl;
            n = get_correct(1, int(cs_map.size()));
            cout << "Input numbers of CSs: " << endl;
            for (int i = 0; i < n; ++i) {
                z = get_correct(1, int(cs_map.size()));
                if (cs_map.find(z) != cs_map.end())
                    ids.insert(z);
            }
            for (auto& i : ids)
                cs_map.erase(i);
            cout << "\nCSs were deleted!" << endl;
        }
        if (h == 1) {
            ids = Cs_filter(cs_map);
            if (ids.size() != 0) {
                for (auto& i : ids)
                    cs_map.erase(i);
                cout << "\nCSs were deleted!" << endl;
            }
        }
    }
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