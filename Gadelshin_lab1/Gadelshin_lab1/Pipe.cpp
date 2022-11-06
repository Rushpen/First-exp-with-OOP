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

unordered_set <int> Pipe::filter_pipe(unordered_map <int, Pipe>& p_map) {
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
                if (pip.second.get_stat() == false)
                    v_id.insert(pip.first);
            }
        }
        if (a == 2) {
            for (auto pip : p_map) {
                if (pip.second.get_stat() == true)
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

void Pipe::edit_pipe(unordered_map <int, Pipe>& p_map) {
    bool a, d;
    int ed, id;
    unordered_set<int>ids;
    if (p_map.size() != 0) {
        cout << "\nChange: 1.Edit one pipe  2.Edit pipes  0.Delete pipe" << endl;
        ed = get_correct(0, 2);
        if (ed == 1) {
            cout << "Input index of pipe: " << endl;
            id = id_check(p_map);
            cout << "\n Choose new pipe status:\n 0.In repair\n 1.In work\n ";
            a = get_correct(0, 1);
            auto pipe = p_map.find(id);
            p_map.at(id).set_stat(a);
            cout << "Changes applied!" << endl;
        }
        if (ed == 2) {
            cout << "Choose method: 0.By ids  1.By filter" << endl;
            d = get_correct(0, 1);
            if (d == 0) {
                int n, z;
                cout << "How many pipes you want to edit?" << endl;
                n = get_correct(1, int(p_map.size()));
                cout << "Input numbers of pipes: " << endl;
                for (int i = 0; i < n; ++i) {
                    z = get_correct(1, int(p_map.size()));
                    if (p_map.find(z) != p_map.end())
                        ids.insert(z);
                }
                cout << "\nInput new status of pipes (0 if repairing, 1 if works)" << endl;
                a = get_correct(0, 1);
                for (auto& i : ids)
                    p_map.at(i).set_stat(a);
                cout << "\nChanges applied!" << endl;
            }
            if (d == 1) {
                ids = filter_pipe(p_map);
                if (ids.size() != 0) {
                    cout << "Enter new status: 0(in repair), 1(ready for operation)" << endl;
                    a = get_correct(0, 1);
                    for (auto& i : ids)
                        p_map.at(i).set_stat(a);
                    cout << "\nChanges applied!" << endl;
                }
            }
        }
        else if (ed == 0) {
            delete_pipes(p_map);
        }
    }
    else
        cout << "There is no Pipe for edit!" << endl;
}

void Pipe::delete_pipes(unordered_map <int, Pipe>& p_map) {
    int id, h;
    bool ed;
    unordered_set<int>ids;
    cout << "Delete: 0.One pipe  1.Pipes" << endl;
    ed = get_correct(0, 1);
    if (ed == 0) {
        cout << "Input index of pipe: " << endl;
        id = id_check(p_map);
        auto pipe = p_map.find(id);
        p_map.erase(pipe);
        cout << "\nPipe deleted" << endl;
    }
    if (ed == 1) {
        bool a;
        cout << "0.By ids  1.By filter" << endl;
        h = get_correct(0, 1);
        if (h == 0) {
            int n, z;
            cout << "How many pipes you want to delete?" << endl;
            n = get_correct(1, int(p_map.size()));
                cout << "Input numbers of pipes: " << endl;
                for (int i = 0; i < n; ++i) {
                    z = get_correct(1, int(p_map.size()));
                    if (p_map.find(z) != p_map.end())
                        ids.insert(z);
            }
            for (auto& i : ids)
                p_map.erase(i);
            cout << "\nPipes were deleted!" << endl;
        }
        if (h == 1) {
            ids = filter_pipe(p_map);
            if (ids.size() != 0) {
                for (auto& i : ids)
                    p_map.erase(i);
                cout << "\nPipes were deleted!" << endl;
            }
        }
    }
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
