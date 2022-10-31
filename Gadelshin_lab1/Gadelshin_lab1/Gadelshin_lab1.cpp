#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Utils.h"
using namespace std;

class Pipe
{
public:
    string name = "";
    bool status = false;
    int pid = 0;
    float lenght = 0;
    float diam = 0;

    friend istream& operator >> (istream& in, Pipe& p);
    friend ostream& operator << (ostream& out, Pipe& p);
    friend ofstream& operator << (ofstream& fcout, Pipe& p);
    friend ifstream& operator >> (ifstream& fcin, Pipe& p);

};

class CS
{
public:
    string name = "";
    int csid = 0, workshops_num = 0, workshops_num_run = 0;
    float efficiency = 0;

    friend istream& operator >> (istream& in, CS& cs);
    friend ostream& operator << (ostream& out, CS& cs);
    friend ofstream& operator << (ofstream& fcout, CS& cs);
    friend ifstream& operator >> (ifstream& fcin, CS& cs);
};

int pid = 0, csid = 0;

void p_status(bool status_p)
{
    if (status_p == false) {
        cout << "status: Pipe in repair\n";
    }
    else {
        cout << "status: Pipe is ready for operation\n";
    }
}

unordered_set <int> filter_pipe(unordered_map <int, Pipe>& p_map) {
    int a;
    unordered_set<int>v_id;
    if (p_map.size() != 0) {
        cout << "Choose:  0.Filter by name 1.Filter by status 'in repair' 2. Filter by status 'working" << endl;
        a = get_correct(0, 2);
        if (a == 0) {
            string n;
            cout << "Input name: " << endl;
            cin >> n;
            for (auto pip : p_map) {
                if (pip.second.name.find(n) != string::npos)
                    v_id.insert(pip.first);
            }
        }
        if (a == 1) {
            for (auto pip : p_map) {
                if (pip.second.status == false)
                    v_id.insert(pip.first);
            }
        }
        if (a == 2) {
            for (auto pip : p_map) {
                if (pip.second.status == true)
                    v_id.insert(pip.first);
            }
        }
        if (v_id.size() == 0)
            cout << "\nThere are no such pipes!" << endl;
    }
    else
        cout << "\nPipes not yet avalaible or have been deleted" << endl;

    for (auto& v : v_id)
        cout << p_map.at(v);
    return v_id;
}
unordered_set <int> CS_filter(unordered_map<int, CS>& cs_map) {
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
                t = ((cst.second.workshops_num - cst.second.workshops_num_run) * 100 / (cst.second.workshops_num));
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

void show_pipe(unordered_map <int, Pipe>& p_map) {
    if (p_map.size()!=0) {
        for (auto p_m : p_map) 
            cout << p_m.second;
    }
    else
        cout << "\nThere is no pipe!"<<endl;
}
void show_cs(unordered_map<int, CS>& cs_map) {
    if (cs_map.size() != 0) {
        for (auto cs_m : cs_map)
            cout << cs_m.second;
    }
    else
        cout << "\nThere is no CS!" << endl;
}

void edit_pipe(unordered_map <int, Pipe>& p_map, int pid) {
    bool a, d;
    int ed;
    unordered_set<int>ids;
    if (p_map.size() != 0) {
        cout << "\nChange: 1.Edit one pipe  2.Edit pipes  0.Delete pipe" << endl;
        ed = get_correct(0 , 2);
        if (ed == 1) {
            cout << "Input index of pipe: " << endl;
            pid = id_check(p_map);
            cout << "\n Choose new pipe status:\n 0.In repair\n 1.In work\n ";
            a = get_correct(0, 1);
            auto pipe = p_map.find(pid);
            p_map.at(pid).status = a;
            cout << "Changes applied!" << endl;
        }
        if (ed == 2) {
            cout << "Choose method: 0.By ids  1.By filter"<<endl;
            d = get_correct(0, 1);
            if (d == 0) {
                int n, z;
                cout << "How many pipes you want to edit?" << endl;
                n = get_correct(1, int (p_map.size()));
                cout << "Input numbers of pipes: " << endl;
                for (int i = 0; i < n; ++i) {
                    z = get_correct(1, int(p_map.size()));
                    if (p_map.find(z) != p_map.end())
                        ids.insert(z);
                }
                cout << "\nInput new status of pipes (0 if repairing, 1 if works)" << endl;
                a = get_correct(0, 1);
                for (auto& i : ids)
                    p_map.at(i).status = a;
                cout << "\nChanges applied!" << endl;
            }
            if (d == 1) {
                ids = filter_pipe(p_map);
                cout << "Enter new status: 0(in repair), 1(ready for operation)" << endl;
                a = get_correct(0, 1);
                for (auto& i : ids)
                    p_map.at(i).status = a;
                cout << "\nChanges applied!" << endl;
            }
        }
        else if (ed == 0){
            cout << "Input index of pipe: " << endl;
            pid = id_check(p_map);
            auto pipe = p_map.find(pid);
            p_map.erase(pipe);
            cout << "\nPipe deleted" << endl;
        }
    }
    else
        cout << "There is no Pipe for edit!"<<endl;
}
void edit_cs(unordered_map<int, CS>& cs_map, int csid) {
    int b, ed;
    bool d;
    unordered_set<int>idcs;
    if (cs_map.size() != 0)
    {
        cout << "\nChange: 1.Edit one CS  2.Edit >1 CS  0.Delete CS" << endl;
        ed = get_correct(0, 2);
        if (ed == 1) {
            cout << "Enter index of CS: ";
            csid = id_check(cs_map);
            cout << "\n Input new number of workshops at work: \n ";
            auto cs = cs_map.find(csid);
            b = get_correct(0, cs_map.at(csid).workshops_num);
            cs_map.at(csid).workshops_num_run = b;
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
                    cs_map.at(ci).workshops_num_run = get_correct(0, cs_map[ci].workshops_num);
                }
                cout << "\nChanges applied" << endl;
            }
            if (d == 1) {
                idcs = CS_filter(cs_map);
                cout << "\nInput new number of working works" << endl;
                for (auto& ci : idcs)
                    cs_map.at(ci).workshops_num_run = get_correct(0, cs_map[ci].workshops_num);
                cout << "\nChanges applied" << endl;
            }
        }

        else if (ed == 0){
            cout << "Enter index of CS: ";
            csid = id_check(cs_map);
            auto cs = cs_map.find(csid);
            cs_map.erase(cs);
            cout << "\nCS deleted" << endl;
        }
    }
    else
        cout << "There is no CS for edit!"<<endl;
}

void save_file(unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map)
{
    string f_n;
    cout << "Input filename: ";
    cin >> f_n;
    ofstream fcout;
    fcout.open(f_n + ".txt");
    if (fcout.is_open())
    {
        fcout << p_map.size() << endl << cs_map.size() << endl;
        for (auto pipe : p_map) {
            fcout << pipe.second;
        }
        for (auto cs : cs_map) {
            fcout << cs.second;
        }
        fcout.close();
        cout << "\nData was successfully written to the file\n";
    }
    else
        cout << "\nError!Failed to open file!";
}
void load_file(unordered_map <int, Pipe>&p_map, unordered_map<int, CS>&cs_map )
{
    int i;
    CS cs;
    Pipe p;
    ifstream fcin;
    string f_n;
    p_map.clear();
    cs_map.clear();
    cout << "Input name of file: ";
    cin >> f_n;
    fcin.open(f_n + ".txt");
    if (fcin.is_open()) {
        fcin >> pid;
        fcin >> csid;
        for (i = 0; i < pid; ++i) {
            fcin>>p;
            p_map.insert({p.pid, p });
        }
        for (i = 0; i < csid; ++i) {
            fcin>>cs;
            cs_map.insert({cs.csid, cs });
        }
        cout << "The data was successfully loaded from the file!";
    }
    else
        cout << "\nError!Failed to open file!";
    fcin.close();
}


int main() {
    unordered_map<int, Pipe>pipe_map;
    unordered_map<int, CS>cs_map;
   int num_option(-1);
    while (num_option) {
        cout << "\nChoose: \n 1.Create pipe 2.Create CS 3.Show all objects" <<
            " 4.Edit Pipe 5.Edit CS 6.Save 7.Load 8.Filter pipe 9.Filter CS 0.Exit\n";
        checking(num_option);
        switch (num_option)     {
        case 1: {
            Pipe P;
            cin >> P;
            pipe_map.insert({ P.pid, P });
            break;
            }
        case 2: {
            CS cs;
            cin >> cs;
            cs_map.insert({ cs.csid, cs });
            break;
            }
        case 3: {
            show_pipe(pipe_map);
            show_cs(cs_map);
            break;
            }
        case 4: {
            edit_pipe(pipe_map, pid);
            break;
            }
        case 5: {
            edit_cs(cs_map, csid );
            break;
            }
        case 6: {
            save_file(pipe_map, cs_map);
            break;
            }
        case 7: {
            load_file(pipe_map, cs_map);
            break;
           }
        case 8: {
            filter_pipe(pipe_map);
            break;
        }
        case 9: {
            CS_filter(cs_map);
            break;
        }
        case 0:{
            return 0;
            break;
        }
        default: {
            cout << "\nERROR! Choose one of the options below!\n\n";
            break;
        }
        }    
    }
}

istream& operator >> (istream& in, Pipe& p) {
    p.pid = ++pid;
    cout << "\nIndex: " << p.pid;
    cout << "\nName: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, p.name);
    cout << "\nLenght: ";
    checking(p.lenght);
    cout << "\nDiameter: ";
    checking(p.diam);
    cout << "\n Choose pipe status:\n 0.In repair\n 1.In work\n ";
    p.status = get_correct(0 , 1);
    p_status(p.status);
    return in;
}
ostream& operator << (ostream& out,Pipe& p)
{
    cout << "\nPipe " << p.pid << "\nname: " << p.name << "\nlenght: "
         << p.lenght << "\ndiameter: " << p.diam << endl;
            p_status(p.status);
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

istream& operator >> (istream& in, CS& cs) {
    cs.csid = ++csid;
    cout << "\nIndex: " << cs.csid;
    cout << "\nName: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "\nNumber of workshops:";
    checking(cs.workshops_num);
    cout << "\nWorkshops at work: ";
    cs.workshops_num_run = get_correct(0, cs.workshops_num);
    cout << "\nEfficiency(0-100):"<<endl;
    cs.efficiency = get_correct(0 , 100);
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

